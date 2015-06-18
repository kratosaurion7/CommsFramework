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

FSize * FRectangle::Size()
{
	FSize* siz = new FSize(Height(), Width());

	return siz;
}
bool FRectangle::IsPointInside(FPosition * pos)
{
	return IsPointInside(pos->X, pos->Y);
}

bool FRectangle::IsPointInside(float x, float y)
{
	if (x < Right && x > Left && y < Bottom && y > Top)
	{
		return true;
	}

	return false;
}

bool FRectangle::Intersect(FRectangle * rec)
{
	// Checks if any corners of the target rectangle is inside my area
	if (IsPointInside(rec->Left, rec->Top) || IsPointInside(rec->Right, rec->Top) ||
		IsPointInside(rec->Right, rec->Bottom) || IsPointInside(rec->Left, rec->Bottom))
	{
		return true;
	}
		
}

Vector2<float>* FRectangle::DistanceFrom(FRectangle * rec, DistanceFromType comparaisonType)
{
	Vector2<float>* distance = new Vector2<float>();

	FPosition* myTargetPosition;
	FPosition* otherTargetPosition;

	switch (comparaisonType)
	{
		case CenterToCenter:
			myTargetPosition = Center();
			otherTargetPosition = rec->Center();
			break;
		case OriginToOrigin:
			myTargetPosition = Origin();
			otherTargetPosition = rec->Origin();
			break;
		default:
			myTargetPosition = Origin();
			otherTargetPosition = rec->Origin();
			break;
	}

	distance->X = myTargetPosition->X - otherTargetPosition->X;
	distance->Y = myTargetPosition->Y - otherTargetPosition->Y;

	delete(myTargetPosition);
	delete(otherTargetPosition);

	return distance;
}
