#ifndef TRACKBARS_H
#define TRACKBARS_H

#define LOWER_HUE "Lower HUE"
#define LOWER_SAT "Lower SAT"
#define LOWER_VAL "Lower VAL"
#define UPPER_HUE "Upper HUE"
#define UPPER_SAT "Upper SAT"
#define UPPER_VAL "Upper VAL"
#define MAX_H 180
#define MAX_SV 256

int coldef = 0;


/**
 * Prototypes
 */
void set_h_upper(int value);
void set_s_upper(int value);
void set_v_upper(int value);
void set_h_lower(int value);
void set_s_lower(int value);
void set_v_lower(int value);
void create_trackbars(const char *wndname);

/**
 *
 */
void create_trackbars(const char *wndname)
{
        cvCreateTrackbar(LOWER_HUE, wndname, &coldef, MAX_H, set_h_lower);
        cvCreateTrackbar(LOWER_SAT, wndname, &coldef, MAX_SV, set_s_lower);
        cvCreateTrackbar(LOWER_VAL, wndname, &coldef, MAX_SV, set_v_lower);

        cvCreateTrackbar(UPPER_HUE, wndname, &coldef, MAX_H, set_h_upper);
        cvCreateTrackbar(UPPER_SAT, wndname, &coldef, MAX_SV, set_s_upper);
        cvCreateTrackbar(UPPER_VAL, wndname, &coldef, MAX_SV, set_v_upper);
}

/**
 *
 */
void set_h_upper(int value)
{
        uhsv.val[0] = value;
}

/**
 *
 */
void set_s_upper(int value)
{
        uhsv.val[1] = value;
}

/**
 *
 */
void set_v_upper(int value)
{
        uhsv.val[2] = value;
}

/**
 *
 */
void set_h_lower(int value)
{
        lhsv.val[0] = value;
}

/**
 *
 */
void set_s_lower(int value)
{
        lhsv.val[1] = value;
}

/**
 *
 */
void set_v_lower(int value)
{
        lhsv.val[2] = value;
}

#endif
