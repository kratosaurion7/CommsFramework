#pragma once

class DX2DTexture;
struct IWICBitmapSource;
class BaseSprite;
class BaseTexture;

#include "Graphic/Base Classes/BaseSprite.h"
#include "DX2DDrawable.h"

class DX2DSprite : public BaseSprite, public DX2DDrawable
{
public:
    DX2DTexture* currentTexture;
    
    DX2DSprite();
    ~DX2DSprite();
    
    virtual IWICBitmapSource* GetDrawableTexture();
    
    virtual BaseTexture* GetCurrentTexture();
    virtual PointerList<BaseTexture*>* GetTextures();
    
    virtual void SetTexture(BaseTexture* texture);
    
    virtual BaseSprite* Clone();
    
    virtual void SetGraphicalFilter(int graphic_filter);
};