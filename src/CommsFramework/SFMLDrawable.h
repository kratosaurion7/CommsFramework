#pragma once

#include <SFML\Graphics.hpp>

class SFMLDrawable
{
protected:
	virtual sf::Drawable* GetDrawableImplementation() = 0;
};
