#pragma once

#include "Vectors.h"

struct MouseClickInfo
{
    bool LeftButtonClicked;
    bool RightButtonClicked;
    bool MiddleButtonClicked;

    FloatVec clickPos;
};