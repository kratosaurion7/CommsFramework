#include "FSize.h"


FSize::FSize()
{
    Height = 0;
    Width = 0;
}

FSize::FSize(float height, float width)
{
    Height = height;
    Width = width;
}


FSize::~FSize()
{
}

void FSize::Set(float h, float w)
{
    Height = h;
    Width = w;
}
