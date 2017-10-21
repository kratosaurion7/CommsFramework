#pragma once

class BaseSprite;
class BaseTexture;
class SDLTexture;
class SDLGraphicEngine;
struct SDL_Texture;

#include "Collections/PointerList.h"
#include "Graphic/Base Classes/BaseSprite.h"
#include "SDLTexture.h"
#include "SDLDrawable.h"

class SDLSprite : public BaseSprite, public SDLDrawable
{
public:
    SDLTexture* currentSpriteTexture; // Private by inheritance

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

    bool hasSendTextureLoadingMessage = false;
};

