#include "SpriteAnimation.h"

#include "BaseTexture.h"

SpriteAnimation::SpriteAnimation()
{
    CurrentFrameRef = NULL;
    Frames = new PointerList<BaseTexture*>();
}


SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::SetFrame(int index)
{
    if (index < Frames->Count())
    {
        CurrentFrameIndex = index;
        CurrentFrameRef = Frames->Get(index);
    }
}

void SpriteAnimation::Advance()
{
    if (CurrentFrameIndex < Frames->Count() - 1)
    {
        CurrentFrameIndex++;
        CurrentFrameRef = Frames->Get(CurrentFrameIndex);
    }
}

void SpriteAnimation::Reset()
{
    CurrentFrameIndex = 0;
}
