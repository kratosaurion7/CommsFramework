#pragma once

#include <SFML\Graphics.hpp>

#include "BaseFont.h"

class SFMLFont : public BaseFont
{
public:
    SFMLFont();
    ~SFMLFont();

    void LoadFontFile(std::string path);

    sf::Font* innerImpl;
private:

};