#pragma once

class Resource;
class BaseTexture;

#include <string>

#include "PointerList.h"

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

