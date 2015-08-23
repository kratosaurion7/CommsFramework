#pragma once

#include "BaseKeyboard.h"

#include "GraphicEngine.h"

class SFMLKeyboard : public BaseKeyboard
{
public:
    SFMLKeyboard();
    ~SFMLKeyboard();

    bool IsKeyPressed(Key key);

    GraphicEngine* graphicsRef;
};

