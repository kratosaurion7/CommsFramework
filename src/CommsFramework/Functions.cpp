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
