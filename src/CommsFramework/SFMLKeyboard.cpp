#include "SFMLKeyboard.h"

#include "Graphical.h"


SFMLKeyboard::SFMLKeyboard()
{
}


SFMLKeyboard::~SFMLKeyboard()
{
}

bool SFMLKeyboard::IsKeyPressed(Key key)
{
    sf::Keyboard::Key convert = (sf::Keyboard::Key)key;

    bool res = sf::Keyboard::isKeyPressed(convert);

    return res;
}
