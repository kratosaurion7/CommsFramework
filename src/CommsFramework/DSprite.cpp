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
}

PointerList<SpriteAnimation*>* DSprite::GetAnimations()
{
    return spriteAnimationList;
}

void DSprite::SetAnimations(PointerList<SpriteAnimation*>* newAnims)
{
    spriteAnimationList = newAnims;

    // TODO : Get default animation from config
    this->DefaultAnimation = newAnims->Get(0);
    this->SetTexture(this->DefaultAnimation->AnimationFrames->Get(0));
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
            returnTextures->AddRange(anim->AnimationFrames);

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

                    CurrentAnimation = NULL;
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
    CurrentAnimation = DefaultAnimation;

    IsPlaying = true;
    LoopAnimation = loop;
}

void DSprite::Play(std::string animName, bool loop)
{
    SpriteAnimation* targetAnimation = NULL;

    targetAnimation = FindAnim(animName);

    if (targetAnimation != NULL)
    {
        CurrentAnimation = targetAnimation;

        IsPlaying = true;
        LoopAnimation = loop;
    }
    else
    {
        // Anim not found.
    }
}

void DSprite::Stop()
{
    IsPlaying = false;
    CurrentAnimation = NULL;
}

void DSprite::Reset()
{
    // TODO : Reset to default anim ?
    this->SetFrame(0);
    IsPlaying = false;
    CurrentAnimation = NULL;
}

void DSprite::NextFrame()
{
    CurrentFrameIndex = (CurrentFrameIndex + 1) % CurrentAnimation->AnimationFrames->Count();
    
    lastFrameTick = GetTicks();

    ApplyCurrentTexture();
}

void DSprite::SetFrame(int index, std::string animName)
{
    if (animName != "")
    {
        SpriteAnimation* anim = FindAnim(animName);

        CurrentFrameIndex = index % anim->AnimationFrames->Count();

        CurrentAnimation = anim;

        this->SetTexture(CurrentAnimation->AnimationFrames->Get(CurrentFrameIndex));
    }
    else
    {
        SpriteAnimation* anim = DefaultAnimation;

        CurrentFrameIndex = index % anim->AnimationFrames->Count();

        this->SetTexture(anim->AnimationFrames->Get(CurrentFrameIndex));
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

BaseSprite* DSprite::Clone()
{
    DSprite* test = new DSprite();

    memcpy(test, this, sizeof(DSprite));

    test->innerImpl = new sf::Sprite();

    this->SetTexture(this->DefaultAnimation->AnimationFrames->Get(0));

    UpdateInnerImpl();

    return test;
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

SpriteAnimation * DSprite::FindAnim(std::string name)
{
    SpriteAnimation* targetAnimation = NULL;

    auto it = this->spriteAnimationList->GetContainer()->begin();
    while (it != this->spriteAnimationList->GetContainer()->end())
    {
        SpriteAnimation* anim = *it;

        if (anim->AnimName.compare(name) == 0)
        {
            targetAnimation = anim;
            break;
        }

        it++;
    }

    return targetAnimation;
}

bool DSprite::IsLastFrame(std::string animName)
{
    return CurrentFrameIndex >= CurrentAnimation->AnimationFrames->Count() - 1;
}

void DSprite::UpdateInnerImpl()
{
    innerImpl->setPosition(position.X, position.Y);
}

void DSprite::ApplyCurrentTexture()
{
    BaseTexture* myTex = CurrentAnimation->AnimationFrames->Get(this->CurrentFrameIndex);

    SetTexture(myTex);
}
