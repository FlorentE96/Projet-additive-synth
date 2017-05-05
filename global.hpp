#ifndef GLOBAL_H
#define GLOBAL_H

#define FALSE (0)
#define TRUE (!FALSE)
#define ON (TRUE)
#define OFF (FALSE)
#define SAMPLE_RATE (44100)
#define LUT_RES (1024)

inline double scale(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif
