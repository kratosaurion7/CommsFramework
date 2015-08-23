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

class BaseMouse {
public:

    virtual bool IsClicked(MouseButtons button) = 0;

    virtual Vector2<float> GetMousePosition() = 0;

};