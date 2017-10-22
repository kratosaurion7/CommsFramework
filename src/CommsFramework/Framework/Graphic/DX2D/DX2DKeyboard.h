#pragma once

#include "Input/Keys.h"
#include "Graphic/Base Classes/BaseKeyboard.h"

class DX2DKeyboard : public BaseKeyboard
{
public:
    DX2DKeyboard();
    ~DX2DKeyboard();
    
    virtual bool IsKeyPressed(Key key);
    
    virtual bool IsKeyClicked(Key key);

    virtual void UpdateKeyboardState();
};