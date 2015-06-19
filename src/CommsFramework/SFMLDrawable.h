#pragma once

#include <SFML\Graphics.hpp>

#include "DrawObject.h"

class SFMLDrawable
{
public:
	virtual sf::Drawable* GetDrawableImplementation() = 0;
};
