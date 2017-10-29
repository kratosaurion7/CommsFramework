#pragma once

class DX2DTexture;
struct ID2D1Bitmap;
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
    
    virtual ID2D1Bitmap* GetDrawableTexture();
    
    virtual BaseTexture* GetCurrentTexture();
    virtual PointerList<BaseTexture*>* GetTextures();
    
    virtual void SetTexture(BaseTexture* texture);
    
    virtual BaseSprite* Clone();
    
    virtual void SetGraphicalFilter(int graphic_filter);

    virtual void UpdateInnerImpl();
};