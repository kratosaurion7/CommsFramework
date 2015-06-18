#pragma once

#include "FPosition.h"

class FRectangle
{
public:
	FRectangle(float x, float y, float h, float w);
	~FRectangle();

	float Width();
	float Height();

	float Left;
	float Top;
	float Right;
	float Bottom;

	FPosition* Origin();
	FPosition* Center();
};

