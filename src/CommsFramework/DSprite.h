#pragma once

#include <SFML\Graphics.hpp>

#include "BaseSprite.h"

#include "BaseTexture.h"
#include "DTexture.h"

#include "SFMLDrawable.h"

#include "FPosition.h"
#include "FRectangle.h"
#include "FSize.h"

class DSprite : public BaseSprite
{
public:
    DSprite();
    ~DSprite();

	virtual DTexture* GetTexture();
	virtual void SetTexture(BaseTexture* texture);

	sf::Sprite* innerImpl;

	sf::Drawable* GetDrawableImplementation();

private:
	DTexture* spriteTexture;

	void UpdateInnerImpl();
};

