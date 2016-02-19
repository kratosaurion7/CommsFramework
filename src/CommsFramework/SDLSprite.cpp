#include "SDLSprite.h"

#include <SDL_render.h>

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
    
    
    SpriteFPS = 15;
    CurrentAnimation = NULL;
    Animations = new PointerList<SpriteAnimation*>();

    LoopAnimation = false;
    IsPlaying = false;
    GravityEnabled = false;

    Engine = NULL;
}


SDLSprite::~SDLSprite()
{
}

SDLTexture* SDLSprite::GetCurrentTexture()
{
    return currentSpriteTexture;
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
    }
}

BaseSprite* SDLSprite::Clone()
{
    return nullptr;
}

SDL_Texture* SDLSprite::GetDrawableTexture()
{
    return currentSpriteTexture->texture;
}

void SDLSprite::UpdateInnerImpl()
{
}