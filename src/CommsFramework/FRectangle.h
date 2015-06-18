#pragma once

#include "FPosition.h"
#include "FSize.h"
#include "Vectors.h"

enum DistanceFromType {
	CenterToCenter,
	OriginToOrigin
};

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

	FSize* Size();

	// Geometry methods

	bool IsPointInside(FPosition* pos);
	bool IsPointInside(float x, float y);
	bool Intersect(FRectangle* rec);

	Vector2<float>* DistanceFrom(FRectangle* rec, DistanceFromType comparaisonType);
};