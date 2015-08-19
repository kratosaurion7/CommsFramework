#pragma once

#include "BaseFont.h"

#include <SFML\Graphics.hpp>

class SFMLFont : public BaseFont
{
public:
    SFMLFont();
    ~SFMLFont();

    void Load(std::string path);

    sf::Font* innerImpl;
private:

};

