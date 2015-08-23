#pragma once

#include "BaseMouse.h"

class SFMLMouse : public BaseMouse
{
public:
    SFMLMouse();
    ~SFMLMouse();

    virtual bool IsClicked(MouseButtons button);

    virtual Vector2<int> GetMousePosition();

};

