#include "BaseSprite.h"

#include "Graphic/DrawObject.h"

#include "Graphic/Base Classes/BaseTexture.h"

#include "Graphic/Base Classes/BaseMouse.h"
#include "Geometry/FRectangle.h"

#include "Graphic/Base Classes/BaseGraphicEngine.h"
#include "Engine/GameEngine.h"
#include "System/Utilities.h"
#include "Filesystem/IOUtilities.h"



BaseSprite::~BaseSprite()
{

}

bool BaseSprite::MouseOver()
{
    FRectangle myRec = this->GetRectangle();

    Vector2<float> mousePos = GameEngine::Mouse->GetMousePosition();

    return myRec.IsPointInside(mousePos);
}

bool BaseSprite::CollisionWith(BaseSprite * other)
{
    FRectangle myRec = this->GetRectangle();
    FRectangle otherRec = other->GetRectangle();

    if (otherRec.Intersect(&myRec))
    {
        return true;
    }
    else
    {
        return false;
    }
}

PointerList<BaseTexture*>* BaseSprite::GetTextures()
{
    return nullptr;
}

void BaseSprite::Draw()
{
    if (FrameReady())
    {
        if (IsAnimated && IsPlaying)
        {
            if (CurrentAnimation != NULL)
            {
                if (LoopAnimation && IsLastFrame())
                {
                    CurrentAnimation->Reset();
                }

                NextFrame();
            }
        }
    }
}

void BaseSprite::Play(bool loop)
{
    IsPlaying = true;
    LoopAnimation = loop;
}

void BaseSprite::Play(std::string animName, bool loop)
{
    IsPlaying = true;
    SetFrame(0, animName);
    LoopAnimation = loop;
}

void BaseSprite::Stop()
{
    IsPlaying = false;
}

void BaseSprite::Reset()
{
    IsPlaying = false;
    CurrentAnimation->Reset();
    CurrentAnimation = NULL;
}

void BaseSprite::AddAnimation(SpriteAnimation* newAnim)
{
    Animations->Add(newAnim);

    IsAnimated = true;

    if (CurrentAnimation == NULL)
        CurrentAnimation = newAnim;

    if (this->GetCurrentTexture() == NULL)
        this->SetTexture(newAnim->Frames->First());
}

void BaseSprite::NextFrame()
{
    if (CurrentAnimation != NULL)
    {
        LastFrameTick = GetTicks();

        CurrentAnimation->Advance(this->LoopAnimation);

        SetTexture(CurrentAnimation->CurrentFrameRef);
    }
}

void BaseSprite::SetFrame(int index, std::string animName)
{
    if (animName == "")
    {
        if (CurrentAnimation != NULL)
        {
            CurrentAnimation->SetFrame(index);
        }
    }
    else
    {
        SpriteAnimation* newAnim = Animations->GetBy([animName](SpriteAnimation* anim) { return anim->AnimName == animName; });

        if (newAnim != NULL)
        {
            CurrentAnimation = newAnim;
            CurrentAnimation->SetFrame(index);
        }
    }
}

bool BaseSprite::IsLastFrame()
{
    return CurrentAnimation->CurrentFrameIndex >= CurrentAnimation->Frames->Count();
}

void BaseSprite::SetTexture(std::string newTexturePath)
{
    assert(newTexturePath != "");

    std::string assetNameFromPath = GetFileName(newTexturePath);

    BaseTexture* tex = Engine->CreateTexture(assetNameFromPath, newTexturePath);

    if (tex == NULL)
        return;

    this->SetTexture(tex);

    this->RequestedTextureName = "";
    this->HasTextureApplied = true;
}

void BaseSprite::SetTextureName(std::string textureName)
{
    if (textureName == "")
    {
        int i = 0;
    }

    this->RequestedTextureName = textureName;
    this->HasTextureApplied = false;
}

void BaseSprite::Reload()
{
    BaseTexture* tex = this->Engine->TextureRepo->GetTextureByName(this->RequestedTextureName);

    if (tex != NULL)
    {
        this->SetTexture(tex);
    }
}

void BaseSprite::Unload()
{
}

bool BaseSprite::FrameReady()
{
    int current = GetTicks();

    if (LastFrameTick + (1000 / SpriteFPS) <= current)
    {
        return true;
    }
    
    return false;
}
