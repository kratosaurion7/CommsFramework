#include "SpriteAnimation.h"

#include "BaseTexture.h"

SpriteAnimation::SpriteAnimation()
{
    CurrentFrameIndex = 0;
    CurrentFrameRef = NULL;
    Frames = new PointerList<BaseTexture*>();
}

SpriteAnimation::SpriteAnimation(PointerList<BaseTexture*>* textures)
{
    Frames->AddRange(textures);
}

SpriteAnimation::SpriteAnimation(BaseTexture** textures, int count)
{
    for (int i = 0; i < count; i++)
    {
        BaseTexture* newTex = textures[i];
        Frames->Add(newTex);
    }
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

void SpriteAnimation::Advance(bool loop)
{
    if (CurrentFrameIndex < Frames->Count() - 1)
    {
        CurrentFrameIndex++;
        CurrentFrameRef = Frames->Get(CurrentFrameIndex);
    }
    else if (loop)
    {
        this->Reset();
    }
}

void SpriteAnimation::Reset()
{
    CurrentFrameIndex = 0;
}
