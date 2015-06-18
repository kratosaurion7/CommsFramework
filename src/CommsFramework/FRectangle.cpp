#include "FRectangle.h"



FRectangle::FRectangle(float x, float y, float h, float w)
{
	Left = x;
	Top = h;
	Right = x + w;
	Bottom = y + h;
}


FRectangle::~FRectangle()
{
}

float FRectangle::Width()
{
	return Right - Left;
}

float FRectangle::Height()
{
	return Bottom - Top;
}

FPosition* FRectangle::Origin()
{
	FPosition* pos = new FPosition(Left, Top);

	return pos;
}

FPosition* FRectangle::Center()
{
	FPosition* pos = new FPosition();

	pos->X = (Right - Left) / 2;
	pos->Y = (Bottom - Top) / 2;

	return pos;
}
