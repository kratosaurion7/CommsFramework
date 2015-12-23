#pragma once

class BaseGraphicEngine;

#include "BaseList.h"
#include "BaseKeyboard.h"

class SFMLKeyboard : public BaseKeyboard
{
public:
    SFMLKeyboard();
    ~SFMLKeyboard();

    bool IsKeyPressed(Key key);

    bool IsKeyClicked(Key key);

    BaseGraphicEngine* graphicsRef;

    void UpdateKeyboardState();

private:
    BaseList<Key>* previousFramePressedKeys;
    BaseList<Key>* currentFramePressedKeys;
    
};