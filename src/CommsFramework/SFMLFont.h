#pragma once

#include <SFML\Graphics.hpp>

#include "BaseFont.h"

class SFMLFont : public BaseFont
{
public:
    SFMLFont();
    ~SFMLFont();

    void Load(std::string path);

    sf::Font* innerImpl;
private:

};