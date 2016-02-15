#pragma once

class BaseTexture;

#include <string>

#include "PointerList.h"


class SpriteAnimation
{
public:
    SpriteAnimation();
    ~SpriteAnimation();

    std::string AnimName;

    int CurrentFrameIndex;
    BaseTexture* CurrentFrameRef;
    PointerList<BaseTexture*>* Frames;

    void SetFrame(int index);
    void Advance();
    void Reset();
};

