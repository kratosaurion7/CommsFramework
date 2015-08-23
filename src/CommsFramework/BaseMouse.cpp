#include "BaseMouse.h"

bool BaseMouse::LeftButtonClicked()
{
    if (Left_Current_State == BTN_CLICKED && Left_Previous_State == BTN_RELEASED)
    {
        return true;
    }

    return false;
}

bool BaseMouse::RightButtonClicked()
{
    if (Right_Current_State == BTN_CLICKED && Right_Previous_State == BTN_RELEASED)
    {
        return true;
    }

    return false;
}

bool BaseMouse::MiddleButtonClicked()
{
    if (Middle_Current_State == BTN_CLICKED && Middle_Previous_State == BTN_RELEASED)
    {
        return true;
    }

    return false;
}

void BaseMouse::UpdateMouseState()
{
    Left_Previous_State = Left_Current_State;
    Right_Previous_State = Right_Current_State;
    Middle_Previous_State = Middle_Current_State;

    Left_Current_State = IsClicked(LEFT) ? BTN_CLICKED : BTN_RELEASED;
    Right_Current_State = IsClicked(RIGHT) ? BTN_CLICKED : BTN_RELEASED;
    Middle_Current_State = IsClicked(MIDDLE) ? BTN_CLICKED : BTN_RELEASED;
}
