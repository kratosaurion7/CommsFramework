#pragma once

#include "BaseMouse.h"

#include "GraphicEngine.h"

class SFMLMouse : public BaseMouse
{
public:
    SFMLMouse();
    ~SFMLMouse();

    GraphicEngine* engineRef;

    virtual bool IsClicked();

    virtual bool IsClicked(MouseButtons button);

    virtual Vector2<float> GetMousePosition();
};

