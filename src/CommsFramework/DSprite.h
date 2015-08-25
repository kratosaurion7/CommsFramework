#pragma once

#include <SFML\Graphics.hpp>

#include "BaseSprite.h"

#include "BaseTexture.h"
#include "DTexture.h"

#include "SFMLDrawable.h"

#include "FPosition.h"
#include "FRectangle.h"
#include "FSize.h"

#include "SpriteAnimation.h"

class DSprite : public BaseSprite, public SFMLDrawable
{
public:
    DSprite();
    ~DSprite();

    virtual DTexture* GetCurrentTexture();

    virtual PointerList<BaseTexture*>* GetTextures();

    virtual void Draw();

    virtual void Play(bool loop = false);
    virtual void Play(std::string animName, bool loop = false);
    virtual void Stop();
    virtual void Reset();

    virtual void NextFrame();
    virtual void SetFrame(int index);
    virtual bool IsLastFrame();

    virtual void SetTexture(BaseTexture* texture);
    virtual void SetTextures(PointerList<BaseTexture*>* textures);

    sf::Sprite* innerImpl;
    sf::Drawable* GetDrawableImplementation();

private:

    bool IsFrameReady();

    int lastFrameTick;

    DTexture* spriteTexture; // Texture currently on sprite.
    //PointerList<DTexture*>* spriteTexturesList;
    PointerList<SpriteAnimation*>* spriteAnimationList;

    void UpdateInnerImpl();
    void ApplyCurrentTexture();
};

