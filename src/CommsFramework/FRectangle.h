#pragma once

#include "FPosition.h"
#include "FSize.h"
#include "Vectors.h"

enum DistanceFromType {
    OriginToOrigin,
    CenterToCenter
};

class FRectangle
{
public:
    FRectangle();
    FRectangle(float x, float y, float h, float w);
    ~FRectangle();

    enum RectangleEdge
    {
        LeftEdge = 1,
        TopEdge = 2,
        RightEdge = 4,
        BottomEdge = 8,
    };


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
    bool IsPointInside(Vector2<float> vec);
    bool IsPointInside(FPosition* pos);
    bool IsPointInside(float x, float y);

    bool Intersect(FRectangle* rec);
    bool Intersect(FRectangle* rec, int thisRectangleEdge);
    bool Intersect(FRectangle* rec, int thisRectangleEdge, int otherRectangleEdge);

    Vector2<float>* DistanceFrom(FRectangle* rec, DistanceFromType comparaisonType = OriginToOrigin);
};

