#pragma once

#include "Geometry/Vectors.h"

struct MouseClickInfo
{
    bool LeftButtonClicked;
    bool RightButtonClicked;
    bool MiddleButtonClicked;

    FloatVec clickPos;
};