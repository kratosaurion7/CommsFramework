#pragma once

#include "BaseKeyboard.h"

#include "GraphicEngine.h"

class SFMLKeyboard : public BaseKeyboard
{
public:
    SFMLKeyboard();
    ~SFMLKeyboard();

    bool IsKeyPressed(Key key);

    bool IsKeyClicked(Key key);

    GraphicEngine* graphicsRef;

    void UpdateKeyboardState();

private:
    BaseList<Key>* previousFramePressedKeys;
    BaseList<Key>* currentFramePressedKeys;
    
};

