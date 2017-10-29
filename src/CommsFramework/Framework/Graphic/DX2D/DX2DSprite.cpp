#ifdef WIN32
#include "DX2DSprite.h"

#include <Windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <wincodecsdk.h>

#include "DX2DTexture.h"

DX2DSprite::DX2DSprite()
{
    currentTexture = NULL;

    Coordinate = VIEWPORT_RELATIVE;

    ClickInfo = NULL;

    isVisible = false;
    position = FPosition();
    positionOffset = FPosition();
    size = FSize();
    scale = FloatVec();
    scale.Set(1, 1);
    clippingBounds = FRectangle();

    SpriteFPS = 1;
    CurrentAnimation = NULL;
    Animations = new PointerList<SpriteAnimation*>();

    LoopAnimation = false;
    IsPlaying = false;
    GravityEnabled = false;

    Engine = NULL;

    HasTextureApplied = false;
    RequestedTextureName = "";

}

DX2DSprite::~DX2DSprite()
{
    
}

ID2D1Bitmap* DX2DSprite::GetDrawableTexture()
{
    return currentTexture->texture;
    
}

BaseTexture* DX2DSprite::GetCurrentTexture()
{
    return currentTexture;
}

PointerList<BaseTexture*>* DX2DSprite::GetTextures()
{
    return NULL;
}

void DX2DSprite::SetTexture(BaseTexture* texture)
{
    currentTexture = (DX2DTexture*)texture;

    this->SetSize(texture->GetSize());
}

BaseSprite* DX2DSprite::Clone()
{
    return NULL;
}

void DX2DSprite::SetGraphicalFilter(int graphic_filter)
{
    
}

void DX2DSprite::UpdateInnerImpl()
{
}

#endif