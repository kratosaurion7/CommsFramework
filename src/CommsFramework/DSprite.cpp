#include "DSprite.h"

#include <SFML\Graphics.hpp>

#include "BaseSprite.h"

#include "BaseTexture.h"
#include "DTexture.h"

#include "FPosition.h"
#include "FSize.h"
#include "FRectangle.h"

#include "Utilities.h"

DSprite::DSprite()
{
    innerImpl = new sf::Sprite();
    spriteTexture = NULL;
    isVisible = true;
    position = new FPosition();
    size = new FSize();
    spriteTexture = NULL;
    spriteTextures = new PointerList<DTexture*>();

    IsPlaying = false;

    SpriteFPS = 60; // TODO : Get monitor FPS
}

DSprite::~DSprite()
{
    // Don't delete the sprite texture when deleting a sprite, the texture might be shared around.
    delete(innerImpl);
    delete(position);
    delete(size);

    if (spriteTextures != NULL)
    {
        spriteTextures->Release();
        delete(spriteTextures);
    }


    //delete(spriteTexture);
}

DTexture* DSprite::GetCurrentTexture()
{
    return spriteTexture;
}

PointerList<BaseTexture*>* DSprite::GetTextures()
{
    PointerList<BaseTexture*>* returnTextures = new PointerList<BaseTexture*>();

    auto it = spriteTextures->GetContainer()->begin();
    while (it != spriteTextures->GetContainer()->end())
    {
        DTexture* texture = (*it);
        returnTextures->Add(texture);
    }

    return returnTextures;
}

void DSprite::Draw()
{
    if (this->IsVisible())
    {
        if (this->IsPlaying)
        {
            if (this->IsFrameReady())
            {
                if (!LoopAnimation && IsLastFrame())
                {
                    this->SetFrame(0);
                }
                else
                {
                    this->NextFrame();
                }
            }
        }
    }
}

void DSprite::Play(bool loop)
{
    IsPlaying = true;
    LoopAnimation = loop;
}

void DSprite::Stop()
{
    IsPlaying = false;
}

void DSprite::NextFrame()
{
    //CurrentFrameIndex++;
    
    CurrentFrameIndex = (CurrentFrameIndex + 1) % FramesCount;
    
    lastFrameTick = GetTicks();

    ApplyCurrentTexture();
}

void DSprite::SetFrame(int index)
{
    spriteTexture = spriteTextures->Get(index % FramesCount); // Modulo for safety.
}

void DSprite::SetTextures(PointerList<BaseTexture*>* textures)
{
    if (spriteTextures != NULL)
        delete(spriteTextures);

    spriteTextures = new PointerList<DTexture*>();

    auto it = textures->GetContainer()->begin();
    while (it != textures->GetContainer()->end())
    {
        BaseTexture* texture = (*it);

        spriteTextures->Add((DTexture*)texture);

        it++;
    }

    FramesCount = spriteTextures->Count();

    if (FramesCount > 0)
    {
        SetTexture(textures->Get(0));
    }
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

sf::Drawable * DSprite::GetDrawableImplementation()
{
    return innerImpl;
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

bool DSprite::IsLastFrame()
{
    return CurrentFrameIndex >= FramesCount - 1;
}

void DSprite::UpdateInnerImpl()
{
    innerImpl->setPosition(position->X, position->Y);
}

void DSprite::ApplyCurrentTexture()
{
    SetTexture(spriteTextures->Get(CurrentFrameIndex));
}
