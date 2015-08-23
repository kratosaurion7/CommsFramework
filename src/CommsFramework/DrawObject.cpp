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
    if (position != NULL)
    {
        return position->X;
    }
    else
    {
        return 0;
    }
}

float DrawObject::GetY()
{
    if (position != NULL)
    {
        return position->Y;
    }
    else
    {
        return 0;
    }
}

void DrawObject::SetX(float value)
{
    if (position != NULL)
    {
        position->X = value;

        UpdateInnerImpl();
    }
}

void DrawObject::SetY(float value)
{
    if (position != NULL)
    {
        position->Y = value;

        UpdateInnerImpl();
    }
}

void DrawObject::IncrementX(float value)
{
    if (position != NULL)
    {
        position->X += value;

        UpdateInnerImpl();
    }
}

void DrawObject::IncrementY(float value)
{
    if (position != NULL)
    {
        position->Y += value;

        UpdateInnerImpl();
    }
}

FPosition * DrawObject::GetPos()
{
    return position;
}

void DrawObject::SetPos(float x, float y)
{
    if (position != NULL)
    {
        position->Set(x, y);

        UpdateInnerImpl();
    }
}

void DrawObject::SetPos(FPosition * value)
{
    if (position != NULL)
        delete position;

    position = value;

    UpdateInnerImpl();
}

void DrawObject::SetCenterPos(FPosition * value)
{
    SetPos(value->X - (GetWidth() / 2), value->Y - (GetHeight() / 2));
}

FRectangle DrawObject::GetRectangle()
{
    //FRectangle* rec = new FRectangle(GetX(), GetY(), GetHeight(), GetWidth());
    FRectangle rec = FRectangle(GetX(), GetY(), GetHeight(), GetWidth());

    return rec;
}

float DrawObject::GetHeight()
{
    if (size != NULL)
    {
        return size->Height;
    }
    else
    {
        return 0;
    }
}

float DrawObject::GetWidth()
{
    if (size != NULL)
    {
        return size->Width;
    }
    else
    {
        return 0;
    }
}

void DrawObject::SetHeight(float height)
{
    if (size != NULL)
    {
        size->Height = height;
    }
}

void DrawObject::SetWidth(float width)
{
    if (size != NULL)
    {
        size->Width = width;
    }
}

FSize * DrawObject::GetSize()
{
    return size;
}

void DrawObject::SetSize(float height, float width)
{
    if (size != NULL)
        delete size;

    size = new FSize(height, width);

}

void DrawObject::SetSize(FSize * value)
{
    if (size != NULL)
        delete size;

    size = value;
}
