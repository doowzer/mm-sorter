#ifndef COLORS_H
#define COLORS_H

/**
 * Globals
 */
#define LOWER 0
#define UPPER 1
#define COLORS 6
#define COLOR_THRESHOLD 5000

enum {
        RED = 0,
        GREEN = 1,
        BLUE = 2,
        YELLOW = 3,
        ORANGE = 4,
        BROWN = 5
};

CvScalar mm_color[COLORS][2];
CvScalar lhsv, uhsv;

/**
 * Prototypes
 */
void init_colors();


/**
 *
 */
void init_colors(void)
{
        mm_color[RED][LOWER] = cvScalar(0, 115, 80, 0);
        mm_color[RED][UPPER] = cvScalar(1, 256, 256, 0);

        mm_color[GREEN][LOWER] = cvScalar(60, 50, 52, 0);
        mm_color[GREEN][UPPER] = cvScalar(70, 256, 256, 0);

        mm_color[BLUE][LOWER] = cvScalar(100, 150, 60, 0);
        mm_color[BLUE][UPPER] = cvScalar(110, 256, 256, 0);

        mm_color[YELLOW][LOWER] = cvScalar(20, 100, 75, 0);
        mm_color[YELLOW][UPPER] = cvScalar(30, 256, 256, 0);

        mm_color[ORANGE][LOWER] = cvScalar(10, 90, 120, 0);
        mm_color[ORANGE][UPPER] = cvScalar(10, 256, 256, 0);

        mm_color[BROWN][LOWER] = cvScalar(16, 26, 0, 0);
        mm_color[BROWN][UPPER] = cvScalar(16, 256, 60, 0);
}

#endif
