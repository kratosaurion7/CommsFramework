#pragma once

class SpriteAnimation;
class BaseSprite;
class BaseTexture;
class SDLTexture;
class SDLGraphicEngine;
class SDL_Texture;

#include "PointerList.h"
#include "SDLTexture.h"

#include "SDLDrawable.h"
#include "BaseSprite.h"

class SDLSprite : public BaseSprite, public SDLDrawable
{
public:
    SDLTexture* currentSpriteTexture;

    SDLSprite();
    ~SDLSprite();

    PointerList<SpriteAnimation*>* GetAnimations();
    void SetAnimations(PointerList<SpriteAnimation*>* newAnims);

    virtual SDLTexture* GetCurrentTexture();
    virtual PointerList<BaseTexture*>* GetTextures();

    virtual void Draw();

    virtual void Play(bool loop = false);
    virtual void Play(std::string animName, bool loop = false);
    virtual void Stop();
    virtual void Reset();

    virtual void NextFrame();
    virtual void SetFrame(int index, std::string animName = "");
    virtual bool IsLastFrame(std::string animName = "");

    virtual void SetTexture(BaseTexture* texture);

    virtual BaseSprite* Clone();

    virtual SDL_Texture* GetDrawableTexture();
private:
    virtual void UpdateInnerImpl();
};

