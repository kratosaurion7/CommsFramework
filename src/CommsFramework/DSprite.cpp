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
    spriteTexture = NULL;
    spriteAnimationList = new PointerList<SpriteAnimation*>();

    IsPlaying = false;

    SpriteFPS = 60; // TODO : Get monitor FPS
}

DSprite::~DSprite()
{
    // Don't delete the sprite texture when deleting a sprite, the texture might be shared around.
    delete(innerImpl);


    if (spriteAnimationList != NULL)
    {
        spriteAnimationList->Release();
        delete(spriteAnimationList);
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

    auto it = spriteAnimationList->GetContainer()->begin();
    while (it != spriteAnimationList->GetContainer()->end())
    {
        SpriteAnimation* anim = (*it);
        
        auto itAnim = anim->AnimationFrames->GetContainer()->begin();
        while (itAnim != anim->AnimationFrames->GetContainer()->end())
        {
            // TODO : Get a texture from a Resource
            itAnim++;
        }


        it++;
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

                    IsPlaying = false;
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

void DSprite::Play(std::string animName, bool loop)
{
}

void DSprite::Stop()
{
    IsPlaying = false;
}

void DSprite::Reset()
{
    this->SetFrame(0);
}

void DSprite::NextFrame(std::string animName)
{
    CurrentFrameIndex = (CurrentFrameIndex + 1) % FramesCount;
    
    lastFrameTick = GetTicks();

    ApplyCurrentTexture();
}

void DSprite::SetFrame(int index, std::string animName)
{
    CurrentFrameIndex = index % FramesCount;

    if (animName != "")
    {

    }
    else
    {
        SpriteAnimation* anim = spriteAnimationList->Get(0);

        this->spriteTexture = anim->AnimationFrames->Get(index % FramesCount); // Modulo for safety.

    }

    spriteTexture = spriteTexturesList->Get(index % FramesCount); 
}

void DSprite::SetTextures(PointerList<BaseTexture*>* textures)
{
    if (spriteTexturesList != NULL)
        delete(spriteTexturesList);

    spriteTexturesList = new PointerList<DTexture*>();

    auto it = textures->GetContainer()->begin();
    while (it != textures->GetContainer()->end())
    {
        BaseTexture* texture = (*it);

        spriteTexturesList->Add((DTexture*)texture);

        it++;
    }

    FramesCount = spriteTexturesList->Count();

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

bool DSprite::IsLastFrame(std::string animName)
{
    return CurrentFrameIndex >= FramesCount - 1;
}

void DSprite::UpdateInnerImpl()
{
    innerImpl->setPosition(position.X, position.Y);
}

void DSprite::ApplyCurrentTexture()
{
    SetTexture(spriteTexturesList->Get(CurrentFrameIndex));
}
