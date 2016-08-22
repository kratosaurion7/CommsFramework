#include "SDLSprite.h"

#include <SDL.h>
#include <SDL_image.h>

#include "BaseSprite.h"
#include "BaseText.h"
#include "BaseTexture.h"
#include "SDLTexture.h"
#include "SDLGraphicEngine.h"
#include "SpriteAnimation.h"

SDLSprite::SDLSprite()
{
    ClickInfo = NULL;

    isVisible = false;
    position = FPosition();
    positionOffset = FPosition();
    size = FSize();
    scale = FloatVec();
    scale.Set(1, 1);
    clippingBounds = FRectangle();
    
    currentSpriteTexture = NULL;
    SpriteFPS = 1;
    CurrentAnimation = NULL;
    Animations = new PointerList<SpriteAnimation*>();

    LoopAnimation = false;
    IsPlaying = false;
    GravityEnabled = false;

    Engine = NULL;

    this->HasTextureApplied = false;
    this->RequestedTextureName = "";
}

SDLSprite::~SDLSprite()
{
}

SDLTexture * SDLSprite::GetCurrentTexture()
{
    if (IsAnimated)
    {
        if (CurrentAnimation != NULL)
        {
            return (SDLTexture*)CurrentAnimation->CurrentFrameRef;
        }
    }
    else
    {
        return this->currentSpriteTexture;
    }

    return NULL;
}

PointerList<BaseTexture*>* SDLSprite::GetTextures()
{
    return nullptr;
}

void SDLSprite::SetTexture(BaseTexture* texture)
{
    if (texture == NULL)
    {
        this->currentSpriteTexture = NULL;
        
        return;
    }

    SDLTexture* sdlTex = dynamic_cast<SDLTexture*>(texture);

    if (sdlTex != NULL)
    {
        currentSpriteTexture = sdlTex;
        size = texture->GetSize();

        this->HasTextureApplied = true;
    }
}

BaseSprite* SDLSprite::Clone()
{
    return nullptr;
}

SDL_Texture* SDLSprite::GetDrawableTexture()
{
    if (currentSpriteTexture == NULL)
    {
        return NULL;
    }

    return currentSpriteTexture->texture;
}

void SDLSprite::SetGraphicalFilter(int graphic_filter)
{
    if (graphic_filter & GRAPHIC_FILTER::NONE)
    {
        SDL_SetTextureAlphaMod(this->currentSpriteTexture->texture, 255);
        //SDL_SetTextureBlendMode(this->currentSpriteTexture->texture, SDL_BLENDMODE_NONE);
        SDL_SetTextureColorMod(this->currentSpriteTexture->texture, 255, 255, 255);

        this->currentSpriteTexture->ResetTextureFromSurface();
    }
    else if (graphic_filter & GRAPHIC_FILTER::GRAYSCALE)
    {
        this->currentSpriteTexture->FreeTexture();

        this->currentSpriteTexture->texture = GrayScaleTextureFromSurface(this->currentSpriteTexture->surface);
    }
    else if (graphic_filter & GRAPHIC_FILTER::ALPHAMOD)
    {
        SDL_SetTextureAlphaMod(this->currentSpriteTexture->texture, 128);
    }
}

void SDLSprite::UpdateInnerImpl()
{
}

SDL_Texture* SDLSprite::GrayScaleTextureFromSurface(SDL_Surface* surface)
{
    SDLGraphicEngine* eng = (SDLGraphicEngine*)this->Engine;

    SDL_Surface* newSurface = SDL_CreateRGBSurface(0, surface->w, surface->h, surface->format->BitsPerPixel, 
        surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

    Uint32* originalPix = (Uint32*)surface->pixels;
    Uint32* newPix = (Uint32*)newSurface->pixels;

    for (int i = 0; i < surface->h; i++)
    {
        for (int j = 0; j < surface->w; j++)
        {
            Uint32 p = originalPix[j + (i * surface->w)];

            Uint8 r;
            Uint8 g;
            Uint8 b;
            Uint8 a;

            SDL_GetRGBA(p, surface->format, &r, &g, &b, &a);

            Uint8 gray = (r + g + b) / 3;

            Uint32 grayColor = SDL_MapRGBA(surface->format, gray, gray, gray, 255);

            newPix[j + (i * surface->w)] = grayColor;
        }
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(eng->gameRenderer, newSurface);

    return tex;
}
