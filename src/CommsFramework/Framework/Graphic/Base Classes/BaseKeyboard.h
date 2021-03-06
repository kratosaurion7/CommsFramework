#pragma once

#include "Input/Keys.h"

class BaseKeyboard
{
public:
    virtual bool IsKeyPressed(Key key) = 0;

    virtual bool IsKeyClicked(Key key) = 0;

    virtual void UpdateKeyboardState() = 0;
};