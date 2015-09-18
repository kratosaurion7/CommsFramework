#pragma once

#include "FPosition.h"
#include "FRectangle.h"
#include "FSize.h"

#include <string>

class DrawObject
{
public:
    std::string Ident;

    virtual void Show(bool show);
    virtual bool IsVisible();

    virtual float GetX();
    virtual float GetY();

    virtual void SetX(float value);
    virtual void SetY(float value);

    virtual void IncrementX(float value);
    virtual void IncrementY(float value);

    virtual FPosition GetPos();
    virtual void SetPos(float x, float y);
    virtual void SetPos(FPosition value);
    virtual void SetCenterPos(FPosition value);

    virtual FRectangle GetRectangle();

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

protected:
    bool isVisible;

    FPosition position;
    FSize size;
    FloatVec scale;

    virtual void UpdateInnerImpl() = 0;
};