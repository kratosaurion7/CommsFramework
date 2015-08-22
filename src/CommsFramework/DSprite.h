#pragma once

#include <SFML\Graphics.hpp>

#include "BaseSprite.h"

#include "BaseTexture.h"
#include "DTexture.h"

#include "SFMLDrawable.h"

#include "FPosition.h"
#include "FRectangle.h"
#include "FSize.h"

class DSprite : public BaseSprite, public SFMLDrawable
{
public:
    DSprite();
    ~DSprite();

    virtual DTexture* GetCurrentTexture();

    virtual PointerList<BaseTexture*>* GetTextures();

    virtual void Draw();

    virtual void Play(bool loop = false);
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

    bool IsPlaying;
    bool LoopAnimation;
    


    DTexture* spriteTexture; // Texture currently on sprite.

    PointerList<DTexture*>* spriteTextures;

    void UpdateInnerImpl();

    void ApplyCurrentTexture();
};

