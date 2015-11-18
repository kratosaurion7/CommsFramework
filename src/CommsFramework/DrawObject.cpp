#include "DrawObject.h"

#include "GameEngine.h"

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

float DrawObject::GetOffsetX()
{
    return this->positionOffset.X;
}

float DrawObject::GetOffsetY()
{
    return this->positionOffset.Y;
}

void DrawObject::SetOffsetX(float value)
{
    this->positionOffset.X = value;

    UpdateInnerImpl();
}

void DrawObject::SetOffsetY(float value)
{
    this->positionOffset.Y = value;

    UpdateInnerImpl();
}

void DrawObject::IncrementOffsetX(float value)
{
    this->positionOffset.X += value;

    this->UpdateInnerImpl();
}

void DrawObject::IncrementOffsetY(float value)
{
    this->positionOffset.Y += value;

    this->UpdateInnerImpl();
}

void DrawObject::ResetOffsets()
{
    this->positionOffset.Set(0, 0);

    this->UpdateInnerImpl();
}

FPosition DrawObject::GetPos()
{
    return position;
}

FPosition DrawObject::GetOffsetPos()
{
    FPosition pos = GetPos();
    pos.X += GetOffsetX();
    pos.Y += GetOffsetY();

    return pos;
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

void DrawObject::SetPos(FRectangle rec)
{
    SetClippingBounds(rec);
    
    SetPos(rec.Left, rec.Top);
}

void DrawObject::SetCenterPos(FPosition value)
{
    SetPos(value.X - (GetWidth() / 2), value.Y - (GetHeight() / 2));
}

FRectangle DrawObject::GetRectangle()
{
    FRectangle rec = FRectangle(GetX() + GetOffsetX(), GetY() + GetOffsetY(), GetHeight(), GetWidth());

    return rec;
}

void DrawObject::SetClippingBounds(FRectangle rec)
{
    clippingBounds = rec;
}

float DrawObject::GetHeight()
{
    return size.Height * this->scale.Y;
}

float DrawObject::GetWidth()
{
    return size.Width * this->scale.X;
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

float DrawObject::GetZIndex()
{
    return zIndex;
}

void DrawObject::SetZIndex(float z)
{
    zIndex = z;
}

bool DrawObject::Clicked(MouseButtons targetButton)
{
    if (isClicked)
    {
        if (targetButton == LEFT)
        {
            return GameEngine::Mouse->LeftButtonClicked();
        }
        else if (targetButton == RIGHT)
        {
            return GameEngine::Mouse->RightButtonClicked();
        }
    }

    return false;
}
