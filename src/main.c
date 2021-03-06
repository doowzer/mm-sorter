/**
 * name: main.c
 * code: Hans Ollonen
 * desc: M&M Sorter
 */
#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "colors.h"
#include "serial.h"
#include "trackbars.h"

/**
 * Globals
 */
#define DELAY 33
#define RAW_WND "raw"
#define HSW_WND "hsv"
#define BIN_WND "binary"

IplImage *raw_frame, *hsv_frame, *bin_frame;
CvSeq *contours;
CvMemStorage *storage;
CvFont font;
int gui = 1, adjust = 0;

/**
 * Prototypes
 */
static void on_mouse(int event, int x, int y, int flags, void *data);
static void get_hsv_color(int y, int x);
static void detect_colors(void);
static void filter(void);
static void print(const char *str);


/**
 *
 */
int main(int argc, char *argv[])
{
        CvCapture *camera = NULL;
        CvSize img_size;
        int key;


        fprintf(stdout, "+ INFO: OpenCV version %d.%d.%d\n", CV_MAJOR_VERSION,
                CV_MINOR_VERSION, CV_SUBMINOR_VERSION);

        camera = cvCaptureFromCAM(-1);
        if (camera == NULL) {
                fprintf(stderr, "- ERROR: cvCaptureFromCAM(-1)\n");
                exit(EXIT_FAILURE);
        }

        cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH, 640);
        cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT, 480);

        cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, 1.0, 0.0, 1, 10);

        raw_frame = cvQueryFrame(camera);
        if (raw_frame == NULL) {
                fprintf(stderr, "- ERROR: cvQueryFrame()\n");
                exit(EXIT_FAILURE);
        }

        img_size = cvGetSize(raw_frame);

        hsv_frame = cvCreateImage(img_size, IPL_DEPTH_8U, 3);
        bin_frame = cvCreateImage(img_size, IPL_DEPTH_8U, 1);

        storage = cvCreateMemStorage(0);

        if (gui) {
                cvNamedWindow(RAW_WND, CV_WINDOW_AUTOSIZE);
                cvMoveWindow(RAW_WND, 0, 0);
        }

        if (adjust) {
                cvNamedWindow(BIN_WND, CV_WINDOW_AUTOSIZE);
                cvMoveWindow(BIN_WND, (img_size.width * 1) + 5, 0);

                cvSetMouseCallback(RAW_WND, on_mouse, NULL);

                create_trackbars(BIN_WND);

                cvNamedWindow(HSW_WND, CV_WINDOW_AUTOSIZE);
        }

        init_colors();

        while (key != 27) {
                raw_frame = cvQueryFrame(camera);
                if (raw_frame == NULL) {
                        break;
                }

                detect_colors();

                if (gui) {
                        cvShowImage(RAW_WND, raw_frame);
                }

                if (adjust) {
                        cvShowImage(BIN_WND, bin_frame);
                        cvShowImage(HSW_WND, hsv_frame);
                }

                key = (char) cvWaitKey(DELAY);
        }

        cvReleaseImage(&raw_frame);
        cvReleaseImage(&hsv_frame);
        cvReleaseImage(&bin_frame);

        cvReleaseMemStorage(&storage);

        cvReleaseCapture(&camera);
        cvDestroyAllWindows();

        return 0;
}

/**
 *
 */
static void on_mouse(int event, int x, int y, int flags, void *data)
{
        if (event == CV_EVENT_LBUTTONDOWN) {
                get_hsv_color(x, y);
        }
}

/**
 *
 */
static void get_hsv_color(int y, int x)
{
        CvScalar c;

        cvCvtColor(raw_frame, hsv_frame, CV_BGR2HSV);
        cvSmooth(hsv_frame, hsv_frame, CV_GAUSSIAN, 1, 1, 0, 0);

        c = cvGet2D(hsv_frame, y, x);

        lhsv = cvScalar(c.val[0], c.val[1], c.val[2], c.val[3]);
        uhsv = cvScalar(c.val[0], c.val[1], c.val[2], c.val[3]);

        cvSetTrackbarPos(LOWER_HUE, BIN_WND, (int) c.val[0]);
        cvSetTrackbarPos(LOWER_SAT, BIN_WND, (int) c.val[1]);
        cvSetTrackbarPos(LOWER_VAL, BIN_WND, (int) c.val[2]);

        cvSetTrackbarPos(UPPER_HUE, BIN_WND, (int) c.val[0]);
        cvSetTrackbarPos(UPPER_SAT, BIN_WND, (int) c.val[1]);
        cvSetTrackbarPos(UPPER_VAL, BIN_WND, (int) c.val[2]);
}

/**
 *
 */
static void detect_colors(void)
{
        int i, color = 0, contour_cnt = 0;
        CvBox2D pos;
        CvScalar rgb;


        cvCvtColor(raw_frame, hsv_frame, CV_BGR2HSV);
        cvSmooth(hsv_frame, hsv_frame, CV_GAUSSIAN, 1, 1, 0, 0);

        for (i = 0; i < COLORS; i++) {

                if (adjust) {
                        cvInRangeS(hsv_frame, lhsv, uhsv, bin_frame);
                } else {
                        cvInRangeS(hsv_frame, mm_color[i][LOWER], mm_color[i][UPPER], bin_frame);
                }

                filter();

                color = cvCountNonZero(bin_frame);

                if (color >= COLOR_THRESHOLD) {
                        switch (i) {
                        case RED:
                                rgb = CV_RGB(255, 0, 0);
                                print("RED");
                                break;

                        case GREEN:
                                rgb = CV_RGB(0, 128, 0);
                                print("GREEN");
                                break;

                        case BLUE:
                                rgb = CV_RGB(0, 0, 255);
                                print("BLUE");
                                break;

                        case YELLOW:
                                rgb = CV_RGB(255, 255, 0);
                                print("YELLOW");
                                break;

                        case ORANGE:
                                rgb = CV_RGB(238, 64, 0);
                                print("ORANGE");
                                break;

                        case BROWN:
                                rgb = CV_RGB(139, 62, 47);
                                print("BROWN");
                                break;

                        default:
                                break;
                        }

                        contour_cnt = cvFindContours(bin_frame, storage,
                                &contours, sizeof(CvContour),
                                CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE,
                                cvPoint(0,0));

                        if (contour_cnt > 0) {
                                for ( ; contours != 0; contours = contours->h_next) {
                                        pos = cvMinAreaRect2(contours, 0);
                                        cvEllipseBox(raw_frame, pos, rgb, 2, 8, 0);
                                }
                        }
                }
        }
}


/**
 * filter - Filter binary image
 *
 * Filter binary image using Smooth, Dilate and Erode.
 */
static void filter(void)
{
        cvSmooth(bin_frame, bin_frame, CV_GAUSSIAN, 3, 3, 0, 0);

        cvDilate(bin_frame, bin_frame, NULL, 4);
        cvDilate(bin_frame, bin_frame, NULL, 4);

        cvErode(bin_frame, bin_frame, NULL, 1);
        cvErode(bin_frame, bin_frame, NULL, 1);
}

/**
 * print - Print text to raw frame
 *
 * Print text to raw frame using cvPutText.
 */
static void print(const char *str)
{
        cvPutText(raw_frame, str, cvPoint(0, 20), &font, CV_RGB(0, 255, 0));
}
