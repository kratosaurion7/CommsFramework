#include "SDLSprite.h"

#include <SDL_render.h>

#include "BaseSprite.h"
#include "BaseText.h"
#include "BaseTexture.h"
#include "SDLTexture.h"
#include "SpriteAnimation.h"
#include "SDLGraphicEngine.h"

SDLSprite::SDLSprite()
{
    ClickInfo = NULL;

    CurrentAnimation = NULL;
    DefaultAnimation = NULL;
    spriteAnimationList = new PointerList<SpriteAnimation*>();

    Engine = NULL;
}


SDLSprite::~SDLSprite()
{
}

PointerList<SpriteAnimation*>* SDLSprite::GetAnimations()
{
    return spriteAnimationList;
}

void SDLSprite::SetAnimations(PointerList<SpriteAnimation*>* newAnims)
{
    if (spriteAnimationList != NULL)
    {
        spriteAnimationList->Release();
        delete(spriteAnimationList);
    }

    spriteAnimationList = newAnims;
    this->DefaultAnimation = newAnims->Get(0);
    this->SetTexture(this->DefaultAnimation->AnimationFrames->Get(0));
}

SDLTexture* SDLSprite::GetCurrentTexture()
{
    return currentSpriteTexture;
}

PointerList<BaseTexture*>* SDLSprite::GetTextures()
{
    return nullptr;
}

void SDLSprite::Draw()
{
}

void SDLSprite::Play(bool loop)
{
}

void SDLSprite::Play(std::string animName, bool loop)
{
}

void SDLSprite::Stop()
{
}

void SDLSprite::Reset()
{
}

void SDLSprite::NextFrame()
{
}

void SDLSprite::SetFrame(int index, std::string animName)
{
}

bool SDLSprite::IsLastFrame(std::string animName)
{
    return false;
}

void SDLSprite::SetTexture(BaseTexture* texture)
{
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