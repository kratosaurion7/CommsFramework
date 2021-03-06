#pragma once

class BaseGraphicEngine;
class FPosition;
class FRectangle;
class FSize;
class BaseMouse;
struct MouseClickInfo;

#include "Graphic/Base Classes/BaseMouse.h"

#include <string>
#include "Geometry/Vectors.h"
#include "Geometry/FPosition.h"
#include "Geometry/FSize.h"
#include "Geometry/FRectangle.h"

class DrawObject
{
public:
    enum GRAPHIC_FILTER
    {
        NONE = 1,
        GRAYSCALE = 2,
        ALPHAMOD = 4,
    };

    enum COORDINATE_TYPE
    {
        VIEWPORT_RELATIVE,
        GAME_ABSOLUTE
    };

    COORDINATE_TYPE Coordinate;

    BaseGraphicEngine* Engine;
    std::string Ident;

    bool PropagateClicks = false;
    MouseClickInfo* ClickInfo;

    virtual void Show(bool show);
    virtual bool IsVisible();

    virtual float GetX();
    virtual float GetY();

    virtual void SetX(float value);
    virtual void SetY(float value);

    virtual void IncrementX(float value);
    virtual void IncrementY(float value);

    virtual float GetOffsetX();
    virtual float GetOffsetY();

    virtual void SetOffsetX(float value);
    virtual void SetOffsetY(float value);

    virtual void IncrementOffsetX(float value);
    virtual void IncrementOffsetY(float value);

    virtual void ResetOffsets();

    virtual FPosition GetPos();
    virtual FPosition GetOffsetPos();
    virtual void SetPos(float x, float y);
    virtual void SetPos(FPosition value);
    virtual void SetPos(FRectangle rec);
    virtual void SetCenterPos(FPosition value);

    virtual FRectangle GetRectangle();

    virtual void SetClippingBounds(FRectangle rec);

    virtual float GetHeight();
    virtual float GetWidth();

    virtual void SetHeight(float height);
    virtual void SetWidth(float width);

    virtual FSize GetSize();
    virtual void SetSize(float height, float width);
    virtual void SetSize(FSize value);

    virtual FloatVec GetScale();
    virtual void SetScale(float factor);
    virtual void SetScale(FloatVec factor);

    virtual float GetZIndex();
    virtual void SetZIndex(int z);
    virtual void SetZIndexOverObject(DrawObject* target);
    virtual void SetZIndexUnderObject(DrawObject* target);

    virtual bool Clicked(MouseButtons targetButton = LEFT);

    virtual void SetGraphicalFilter(int graphic_filter) = 0;

protected:
    bool isVisible;

    FPosition position;
    FPosition positionOffset;
    FSize size;
    FloatVec scale;
    FRectangle clippingBounds;

    GRAPHIC_FILTER DrawObjectFilter;

    float zIndex;

    virtual void UpdateInnerImpl() = 0;
};