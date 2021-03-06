#pragma once

#include "Geometry/FSize.h"
#include <string>

class GraphicEngineInitParams
{
public:
    FSize* WindowSize;
    std::string WindowTitle;

    bool EnableVerticalSync = true;
};

