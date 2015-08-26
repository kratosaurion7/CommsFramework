#pragma once

#include "DrawObject.h"
#include "BaseTexture.h"

#include "PointerList.h"
#include "SpriteAnimation.h"

#include <string>

class BaseSprite : public DrawObject
{
public:
    int CurrentFrameIndex = 0;
    int FramesCount = 0;
    int SpriteFPS = 0;
    bool LoopAnimation;
    bool IsPlaying;
    SpriteAnimation* CurrentAnimation;
    SpriteAnimation* DefaultAnimation;

    bool Clicked();

    bool MouseOver();

    virtual PointerList<SpriteAnimation*>* GetAnimations() = 0;
    virtual void SetAnimations(PointerList<SpriteAnimation*>* newAnims) = 0;
    virtual BaseTexture* GetCurrentTexture() = 0;
    virtual PointerList<BaseTexture*>* GetTextures() = 0;

    virtual void Draw() = 0;

    virtual void Play(bool loop = false) = 0;
    virtual void Play(std::string animName, bool loop = false) = 0;
    virtual void Stop() = 0;
    virtual void Reset() = 0;

    virtual void NextFrame() = 0;
    virtual void SetFrame(int index, std::string animName = "") = 0;
    virtual bool IsLastFrame(std::string animName = "") = 0;

    virtual void SetTexture(BaseTexture* texture) = 0;
    //virtual void SetTextures(PointerList<BaseTexture*>* textures) = 0;
};

