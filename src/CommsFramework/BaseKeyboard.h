#pragma once

#include "Keys.h"

class BaseKeyboard
{
public:
    virtual bool IsKeyPressed(Key key) = 0;
};