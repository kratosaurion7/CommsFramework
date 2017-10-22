#pragma once

#include "Geometry/Vectors.h"
#include "Graphic/Base Classes/BaseMouse.h"

class DX2DMouse : public BaseMouse
{
public:
    DX2DMouse();
    ~DX2DMouse();
    
    virtual bool IsClicked();
    virtual bool IsClicked(MouseButtons button);

    virtual Vector2<float> GetMousePosition();
};