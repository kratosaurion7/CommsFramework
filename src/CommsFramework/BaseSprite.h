#pragma once

class DrawObject;
class BaseSprite;
class BaseTexture;
class SpriteDescriptor;
class BaseMouse;


#include "PointerList.h"
#include <string>

#include "DrawObject.h"

class BaseSprite : public DrawObject
{
public:

    /* Animation properties */
    int CurrentFrameIndex = 0;
    int FramesCount = 0;
    int SpriteFPS = 0;
    bool LoopAnimation;
    bool IsPlaying;

    
    bool GravityEnabled;

    bool MouseOver();

    bool CollisionWith(BaseSprite* other);

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
    virtual void SetTexture(std::string newTexturePath);

    virtual BaseSprite* Clone() = 0;
};