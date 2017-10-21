#include "FPosition.h"

#include "Geometry/FRectangle.h"

FPosition::FPosition()
{
    X = 0;
    Y = 0;
}

FPosition::FPosition(float x, float y)
{
    X = x;
    Y = y;
}


FPosition::~FPosition()
{
}

void FPosition::Set(float x, float y)
{
    X = x;
    Y = y;
}