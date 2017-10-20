#pragma once

class BaseTexture;

#include <string>

#include "PointerList.h"

class SpriteAnimation
{
public:
    SpriteAnimation();
    SpriteAnimation(PointerList<BaseTexture*>* textures);
    SpriteAnimation(BaseTexture** textures, int count);
    ~SpriteAnimation();

    std::string AnimName;

    int CurrentFrameIndex;
    BaseTexture* CurrentFrameRef;
    PointerList<BaseTexture*>* Frames;

    void SetFrame(int index);
    void Advance(bool loop = false);
    void Reset();
};

