#pragma once

#include <SFML\Graphics.hpp>

class SFMLDrawable
{
public:
    virtual sf::Drawable* GetDrawableImplementation() = 0;
};