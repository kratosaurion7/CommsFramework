#pragma once

#include "DrawObject.h"
#include "BaseTexture.h"

class BaseSprite : public DrawObject
{
public:
	virtual BaseTexture* GetTexture() = 0;
	virtual void SetTexture(BaseTexture* texture) = 0;
};

