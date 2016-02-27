#pragma once

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

    virtual SDLTexture* GetCurrentTexture();
    virtual PointerList<BaseTexture*>* GetTextures();

    virtual void SetTexture(BaseTexture* texture);

    virtual BaseSprite* Clone();

    virtual SDL_Texture* GetDrawableTexture();

    virtual void SetGraphicalFilter(int graphic_filter);
private:
    virtual void UpdateInnerImpl();

    SDL_Texture* GrayScaleTextureFromSurface(SDL_Surface* surface);
};

