#pragma once

class DrawObject;
class BaseSprite;
class BaseTexture;
class SpriteDescriptor;
class BaseMouse;

#include <string>

#include "Graphic/DrawObject.h"
#include "Collections/PointerList.h"
#include "Graphic/Animation/SpriteAnimation.h"

class BaseSprite : public DrawObject
{
public:
    ~BaseSprite();

    /* Animation properties */
    int SpriteFPS = 0;
    bool LoopAnimation = false;
    bool IsPlaying = true;
    bool IsAnimated = false;

    SpriteAnimation* CurrentAnimation;
    PointerList<SpriteAnimation*>* Animations;

    // Property should probably be moved to Actor.
    bool GravityEnabled;

    bool MouseOver();

    bool CollisionWith(BaseSprite* other);

    virtual BaseTexture* GetCurrentTexture() = 0;
    virtual PointerList<BaseTexture*>* GetTextures();

    virtual void Draw();

    virtual void Play(bool loop = false);
    virtual void Play(std::string animName, bool loop = false);
    virtual void Stop();
    virtual void Reset();

    virtual void AddAnimation(SpriteAnimation* newAnim);
    virtual void NextFrame();
    virtual void SetFrame(int index, std::string animName = "");
    virtual bool IsLastFrame();

    virtual void SetTexture(BaseTexture* texture) = 0;
    virtual void SetTexture(std::string newTexturePath);
    
    virtual void SetTextureName(std::string textureName);

    virtual void Reload();
    virtual void Unload();

    virtual BaseSprite* Clone() = 0;

protected:
    int LastFrameTick = 0;

    bool FrameReady();

    bool HasTextureApplied; // Is true if the sprite has a texture set, false if the texture is requested but not loaded yet.
    std::string RequestedTextureName;

};