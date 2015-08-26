#pragma once

#include <string>

#include "PointerList.h"
#include "Resource.h"
#include "BaseTexture.h"

class SpriteAnimation
{
public:
    SpriteAnimation();
    ~SpriteAnimation();

    std::string AnimName;

    PointerList<Resource*>* AnimationResources;

    PointerList<BaseTexture*>* AnimationFrames;

    void LoadAllResources();
};

