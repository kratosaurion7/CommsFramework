#include "DSprite.h"

#include "BaseTexture.h"
#include "DTexture.h"
#include "FPosition.h"
#include "FRectangle.h"
#include "FSize.h"
#include "GameEngine.h"
#include "Utilities.h"

#include "BaseGraphicEngine.h"

DSprite::DSprite()
{
    innerImpl = new sf::Sprite();
    isVisible = false;
    spriteTexture = NULL;

    IsPlaying = false;
    GravityEnabled = false;
    scale = FloatVec();
    zIndex = 0;
    scale.Set(1, 1);

    ClickInfo = NULL;

    SpriteFPS = 60; // TODO : Get monitor FPS
}

DSprite::~DSprite()
{
    // Don't delete the sprite texture when deleting a sprite, the texture might be shared around.
    delete(innerImpl);

}

DTexture* DSprite::GetCurrentTexture()
{
    return spriteTexture;
}

PointerList<BaseTexture*>* DSprite::GetTextures()
{
    return NULL;
}

void DSprite::Draw()
{
}

void DSprite::Play(bool loop)
{
}

void DSprite::Play(std::string animName, bool loop)
{
}

void DSprite::Stop()
{
}

void DSprite::Reset()
{
}

void DSprite::NextFrame()
{
}

void DSprite::SetFrame(int index, std::string animName)
{
}

void DSprite::SetTexture(BaseTexture * texture)
{
    DTexture* dtxr = dynamic_cast<DTexture*>(texture);

    if (dtxr != NULL)
    {
        innerImpl->setTexture((*dtxr->innerImpl));
        spriteTexture = dtxr;
        size = texture->GetSize();
    }
}

BaseSprite* DSprite::Clone()
{
    return NULL;
}

void DSprite::SetGraphicalFilter(int graphic_filter)
{
    
}

sf::Drawable * DSprite::GetDrawableImplementation()
{
    return innerImpl;
}

bool DSprite::IsAnimatedSprite()
{
    return false;
}

bool DSprite::IsFrameReady()
{
    int currentTickTime = GetTicks();

    if (currentTickTime - lastFrameTick > (1000 / SpriteFPS))
    {
        return true;
    }

    return false;
}

bool DSprite::IsLastFrame(std::string animName)
{
    return false;
}

void DSprite::SetZIndex(int z)
{
    DrawObject::SetZIndex(z);

    this->Engine->FlagForZIndexSorting();
}

void DSprite::UpdateInnerImpl()
{
    innerImpl->setPosition(position.X + positionOffset.X, position.Y + positionOffset.Y);

    innerImpl->setScale(this->scale.X, this->scale.Y);
}

void DSprite::ApplyCurrentTexture()
{
}