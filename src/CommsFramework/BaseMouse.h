#pragma once

#include "Vectors.h"

enum MouseButtons
{
    LEFT,
    RIGHT,
    MIDDLE,
    BUTTON3,
    BUTTON4,
};

enum ButtonState
{
    BTN_CLICKED,
    BTN_RELEASED
};

class BaseMouse {
public:
    virtual bool IsClicked() = 0;
    virtual bool IsClicked(MouseButtons button) = 0;

    ButtonState Left_Previous_State;
    ButtonState Right_Previous_State;
    ButtonState Middle_Previous_State;

    ButtonState Left_Current_State;
    ButtonState Right_Current_State;
    ButtonState Middle_Current_State;
    
    bool LeftButtonClicked();
    bool RightButtonClicked();
    bool MiddleButtonClicked();

    void UpdateMouseState();

    virtual Vector2<float> GetMousePosition() = 0;

};