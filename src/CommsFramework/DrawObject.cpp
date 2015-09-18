#include "DrawObject.h"

void DrawObject::Show(bool show)
{
    isVisible = show;
}

bool DrawObject::IsVisible()
{
    return isVisible;
}

float DrawObject::GetX()
{
    return position.X;
}

float DrawObject::GetY()
{
    return position.Y;
}

void DrawObject::SetX(float value)
{
    position.X = value;

    UpdateInnerImpl();    
}

void DrawObject::SetY(float value)
{
    position.Y = value;

    UpdateInnerImpl();    
}

void DrawObject::IncrementX(float value)
{
    position.X += value;

    UpdateInnerImpl();    
}

void DrawObject::IncrementY(float value)
{
    position.Y += value;

    UpdateInnerImpl();    
}

FPosition DrawObject::GetPos()
{
    return position;
}

void DrawObject::SetPos(float x, float y)
{
    position.Set(x, y);

    UpdateInnerImpl();    
}

void DrawObject::SetPos(FPosition value)
{
    position = value;

    UpdateInnerImpl();
}

void DrawObject::SetCenterPos(FPosition value)
{
    SetPos(value.X - (GetWidth() / 2), value.Y - (GetHeight() / 2));
}

FRectangle DrawObject::GetRectangle()
{
    FRectangle rec = FRectangle(GetX(), GetY(), GetHeight(), GetWidth());

    return rec;
}

float DrawObject::GetHeight()
{
    return size.Height;
}

float DrawObject::GetWidth()
{
    return size.Width;
}

void DrawObject::SetHeight(float height)
{
    size.Height = height;
}

void DrawObject::SetWidth(float width)
{
    size.Width = width;
    
}

FSize DrawObject::GetSize()
{
    return size;
}

void DrawObject::SetSize(float height, float width)
{
    size = FSize(height, width);
}

void DrawObject::SetSize(FSize value)
{
    size = value;
}

FloatVec DrawObject::GetScale()
{
    return this->scale;
}

void DrawObject::SetScale(float factor)
{
    this->scale.X = factor;
    this->scale.Y = factor;

    UpdateInnerImpl();
}

void DrawObject::SetScale(FloatVec factor)
{
    this->scale = factor;

    UpdateInnerImpl();
}
