#pragma once

#include "DrawObject.h"
#include "BaseTexture.h"

#include "PointerList.h"

#include <string>

class BaseSprite : public DrawObject
{
public:
    int CurrentFrameIndex = 0;

    int FramesCount = 0;

    virtual BaseTexture* GetCurrentTexture() = 0;

    virtual PointerList<BaseTexture*>* GetTextures() = 0;

    virtual void SetFrame(int index) = 0;

    virtual void SetTexture(BaseTexture* texture) = 0;
    virtual void SetTextures(PointerList<BaseTexture*>* textures) = 0;
	
	//virtual void UpdateInnerImpl() = 0;
};

