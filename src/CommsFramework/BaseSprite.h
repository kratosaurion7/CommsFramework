#pragma once

#include "DrawObject.h"
#include "BaseTexture.h"

#include <string>

class BaseSprite : public DrawObject
{
public:
	
	std::string SomethingTest;

	void DoStuff();
	
	virtual BaseTexture* GetTexture() = 0;
	virtual void SetTexture(BaseTexture* texture) = 0;

	virtual void UpdateInnerImpl() = 0;

};

