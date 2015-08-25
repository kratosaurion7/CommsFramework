#pragma once

#include "PointerList.h"
#include "Resource.h"

class SpriteAnimation
{
public:
    SpriteAnimation();
    ~SpriteAnimation();

    std::string AnimName;

    PointerList<Resource*>* AnimationResources;
};

