#ifdef WIN32
#include "DX2DMouse.h"
#include <stdio.h>

DX2DMouse::DX2DMouse()
{
    MouseCoordX = 0;
    MouseCoordY = 0;
    
    Left_Previous_State = BTN_RELEASED;
    Right_Previous_State = BTN_RELEASED;
    Middle_Previous_State = BTN_RELEASED;
    
    Left_Current_State = BTN_RELEASED;
    Right_Current_State = BTN_RELEASED;
    Middle_Current_State = BTN_RELEASED;
}

DX2DMouse::~DX2DMouse()
{
    
}

bool DX2DMouse::IsClicked()
{
    return IsClicked(LEFT);
}

bool DX2DMouse::IsClicked(MouseButtons button)
{
    switch (button)
    {
        case LEFT:

            if (this->Left_Current_State == BTN_CLICKED)
            {
                printf("I'm clicked !");
                return true;
            }
            else
            {
                return false;
            }

            return this->Left_Current_State == BTN_CLICKED;
            break;
        case RIGHT:
            return this->Right_Current_State == BTN_CLICKED;
            break;
        case MIDDLE:
            return this->Middle_Current_State == BTN_CLICKED;
            break;
        default:
            return false;
            break;
    }
}

Vector2<float> DX2DMouse::GetMousePosition()
{
    return Vector2<float>(MouseCoordX, MouseCoordY);
}
#endif