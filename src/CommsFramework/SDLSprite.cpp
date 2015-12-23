#include "SDLSprite.h"

#include "BaseSprite.h"
#include "BaseText.h"
#include "BaseTexture.h"

#include "SDLTexture.h"

#include "SpriteAnimation.h"

#include "SDLGraphicEngine.h"

SDLSprite::SDLSprite()
{
}


SDLSprite::~SDLSprite()
{
}

PointerList<SpriteAnimation*>* SDLSprite::GetAnimations()
{
    return nullptr;
}

void SDLSprite::SetAnimations(PointerList<SpriteAnimation*>* newAnims)
{
}

SDLTexture * SDLSprite::GetCurrentTexture()
{
    return nullptr;
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

void SDLSprite::SetTexture(BaseTexture * texture)
{
}

BaseSprite* SDLSprite::Clone()
{
    return nullptr;
}

void SDLSprite::UpdateInnerImpl()
{
}
