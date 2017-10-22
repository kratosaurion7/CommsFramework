#ifdef WIN32
#include "DX2DMouse.h"

DX2DMouse::DX2DMouse()
{
    
}

DX2DMouse::~DX2DMouse()
{
    
}

bool DX2DMouse::IsClicked()
{
    return false;
}

bool DX2DMouse::IsClicked(MouseButtons button)
{
    return false;
}

Vector2<float> DX2DMouse::GetMousePosition()
{
    return Vector2<float>();
}
#endif