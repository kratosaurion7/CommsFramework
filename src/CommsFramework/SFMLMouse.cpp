#include "SFMLMouse.h"

#include <SFML/Graphics.hpp>



SFMLMouse::SFMLMouse()
{
}


SFMLMouse::~SFMLMouse()
{
}

bool SFMLMouse::IsClicked(MouseButtons button)
{
    return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
}

Vector2<int> SFMLMouse::GetMousePosition()
{
    sf::Vector2i pos = sf::Mouse::getPosition();

    Vector2<int> ret;
    ret.X = pos.x;
    ret.Y = pos.y;

    return ret;
}
