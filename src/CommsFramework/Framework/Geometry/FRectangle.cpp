#include "FRectangle.h"

#include "Geometry/FPosition.h"
#include "Geometry/FSize.h"
#include "Geometry/Vectors.h"

FRectangle::FRectangle()
{
}

FRectangle::FRectangle(float x, float y, float h, float w) // TODO : Change order
{
    this->Set(x, y, h, w);
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

void FRectangle::Set(float x, float y)
{
    float currentWidth = this->Width();
    float currentHeight = this->Height();

    this->Set(x, y, currentWidth, currentHeight);
}

void FRectangle::Set(float x, float y, float w, float h)
{
    Left = x;
    Top = y;
    Right = x + w;
    Bottom = y + h;
}

void FRectangle::IncrementX(float amount)
{
    this->Set(this->Left + amount, this->Top, this->Width(), this->Height());
}

void FRectangle::IncrementY(float amount)
{
    this->Set(this->Left, this->Top + amount, this->Width(), this->Height());
}

FPosition FRectangle::Origin()
{
	FPosition pos = FPosition(Left, Top);
	

    return pos;
}

FPosition FRectangle::Center()
{
	FPosition pos;

    pos.X = (Right - Left) / 2;
    pos.Y = (Bottom - Top) / 2;

    return pos;
}

FSize FRectangle::Size()
{
    // TODO : Stop returning goddamn pointers.
    FSize siz = FSize(Height(), Width());

    return siz;
}

bool FRectangle::IsPointInside(Vector2<float> vec)
{
    return IsPointInside(vec.X, vec.Y);
}

bool FRectangle::IsPointInside(FPosition* pos)
{
    return IsPointInside(pos->X, pos->Y);
}

bool FRectangle::IsPointInside(float x, float y)
{
    if (x <= Right && x >= Left && y <= Bottom && y >= Top)
    {
        return true;
    }

    return false;
}

bool FRectangle::Intersect(FRectangle* rec)
{
    // Checks if any corners of the target rectangle is inside my area
    if (IsPointInside(rec->Left, rec->Top) || IsPointInside(rec->Right, rec->Top) ||
        IsPointInside(rec->Right, rec->Bottom) || IsPointInside(rec->Left, rec->Bottom))
    {
        return true;
    }

    return false;
}

bool FRectangle::Intersect(FRectangle* rec, int thisRectangleEdge)
{
    bool result = false;

    if (LeftEdge & thisRectangleEdge)
    {
        bool leftEdgeCollide = false;


        result = result || leftEdgeCollide;
    }
    if (TopEdge & thisRectangleEdge)
    {
        bool topEdgeCollide = false;



        result = result || topEdgeCollide;
    }
    if (RightEdge & thisRectangleEdge)
    {
        bool rightEdgeCollision = false;



        result = result || rightEdgeCollision;
    }
    if (BottomEdge & thisRectangleEdge)
    {
        bool bottomEdgeCollision = false;

        if (this->Bottom >= rec->Top &&
            this->Left >= rec->Left &&
            this->Right <= rec->Right)
        {
            bottomEdgeCollision = true;
        }

        result = result || bottomEdgeCollision;
    }

    return result;
}

bool FRectangle::Intersect(FRectangle * rec, int thisRectangleEdge, int otherRectangleEdge)
{
    return false;
}

FPosition FRectangle::GetCorner(RectangleCorner corner)
{
	switch (corner)
	{
		case FRectangle::TopLeft:
			return FPosition(Left, Top);
		case FRectangle::TopRight:
			return FPosition(Right, Top);
		case FRectangle::BottomRight:
			return FPosition(Right, Bottom);
		case FRectangle::BottomLeft:
			return FPosition(Left, Bottom);
		default:
			return FPosition(-1, -1);
	}
}

Vector2<float> FRectangle::DistanceFrom(FRectangle rec, DistanceFromType comparaisonType)
{
	Vector2<float> distance;

    FPosition myTargetPosition;
    FPosition otherTargetPosition;

    switch (comparaisonType)
    {
    case CenterToCenter:
        myTargetPosition = Center();
        otherTargetPosition = rec.Center();
        break;
    case OriginToOrigin:
        myTargetPosition = Origin();
        otherTargetPosition = rec.Origin();
        break;
    default:
        myTargetPosition = Origin();
        otherTargetPosition = rec.Origin();
        break;
    }

    distance.X = myTargetPosition.X - otherTargetPosition.X;
    distance.Y = myTargetPosition.Y - otherTargetPosition.Y;

    return distance;
}
