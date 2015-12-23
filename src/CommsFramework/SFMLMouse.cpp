#include "SFMLMouse.h"

#include <SFML/Graphics.hpp>

#include "BaseGraphicEngine.h"
#include "GraphicEngine.h"

SFMLMouse::SFMLMouse()
{
}

SFMLMouse::~SFMLMouse()
{
}

bool SFMLMouse::IsClicked()
{
    return this->LeftButtonClicked() || this->RightButtonClicked() || this->MiddleButtonClicked();

    for (int i = 0; i < sf::Mouse::ButtonCount; i++)
    {
        if (sf::Mouse::isButtonPressed((sf::Mouse::Button)i))
        {
            return true;
        }
    }

    return false;
}

bool SFMLMouse::IsClicked(MouseButtons button)
{
    return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
}

Vector2<float> SFMLMouse::GetMousePosition()
{
    GraphicEngine* eng = (GraphicEngine*)engineRef;

    sf::Vector2i pos = sf::Mouse::getPosition(*eng->MainWindow);

    Vector2<float> ret;
    ret.X = pos.x;
    ret.Y = pos.y;

    return ret;
}
