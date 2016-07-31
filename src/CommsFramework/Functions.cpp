#include "Functions.h"

#include <cmath>

float* CreateSinusTrack(int amount, int amplitude)
{
    float* ret = new float[amount];

    for (int i = 0; i < amount; i++)
    {
        ret[i] = sin(i + 1) * amplitude;
    }

    return ret;
}

float* SmoothCurveTrack(float* track, int trackLength, int factor)
{
    float* smoothedCurve = new float[trackLength * factor];

    int k = 0;
    for (int i = 0; i < trackLength; i++)
    {
        float nbOne = track[i];
        float nbTwo = track[i + 1];

        float diff = nbTwo - nbOne;
        float increments = diff / factor;

        smoothedCurve[k++] = nbOne;
        for (int j = 1; j < factor; j++)
        {
            smoothedCurve[k++] = nbOne + (increments * j);
        }
    }

    return smoothedCurve;
}

int avg(int one, int two)
{
    return (one + two) / 2;
}

float favg(float one, float two)
{
    return (one + two) / 2;
}
