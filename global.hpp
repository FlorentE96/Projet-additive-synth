#ifndef GLOBAL_H
#define GLOBAL_H

#define FALSE (0)
#define TRUE (!FALSE)
#define ON (TRUE)
#define OFF (FALSE)
#define SAMPLE_RATE (44100)
#define LUT_RES (1024)

inline float scale(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif
