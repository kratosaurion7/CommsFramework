#include "Functions.h"

#include <cmath>
#include <cassert>

#include "TgaFile.h"

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
    for (int i = 0; i < trackLength - 1; i++)
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

TgaFile* PlotSequenceToImage(float* curve, int curveLength)
{
    int highestPoint = 0;
    int lowestPoint = 0;
    int imageHeight;

    for (int i = 0; i < curveLength; i++)
    {
        int pt = ceil(curve[i]);

        if (pt > highestPoint)
            highestPoint = pt;

        if (pt < lowestPoint)
            lowestPoint = pt;
    }

    imageHeight = abs(highestPoint) + abs(lowestPoint);
    
    assert(imageHeight > 0);

    TgaFile* image = new TgaFile();
    image->Init(curveLength, imageHeight);

    for (int i = 0; i < curveLength; i++)
    {
        int pt = curve[i];
        int baseLine = i + (curveLength * imageHeight / 2);

        TgaPix* px = image->Get(i, (imageHeight / 2) + pt);
        px->a = 255;
        px->r = 255;
        px->g = 0;
        px->b = 255;
    }

    return image;
}
