#ifdef WIN32
#include "DX2DSprite.h"

#include <Windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <wincodecsdk.h>

DX2DSprite::DX2DSprite()
{
    
}

DX2DSprite::~DX2DSprite()
{
    
}

IWICBitmapSource* DX2DSprite::GetDrawableTexture()
{
    return NULL;
}

BaseTexture* DX2DSprite::GetCurrentTexture()
{
    return NULL;
}

PointerList<BaseTexture*>* DX2DSprite::GetTextures()
{
    return NULL;
}

void DX2DSprite::SetTexture(BaseTexture* texture)
{
    
}

BaseSprite* DX2DSprite::Clone()
{
    return NULL;
}

void DX2DSprite::SetGraphicalFilter(int graphic_filter)
{
    
}

#endif