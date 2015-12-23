#pragma once

class BaseGraphicEngine;

#include "Vectors.h"
#include "BaseMouse.h"

class SFMLMouse : public BaseMouse
{
public:
    SFMLMouse();
    ~SFMLMouse();

    BaseGraphicEngine* engineRef;

    virtual bool IsClicked();

    virtual bool IsClicked(MouseButtons button);

    virtual Vector2<float> GetMousePosition();
};

