#pragma once

#include <SFML\Graphics.hpp>

#include "BaseFont.h"

class SFMLFont : public BaseFont
{
public:
    SFMLFont();
    ~SFMLFont();

    void LoadFontFile(std::string path);

    virtual void LoadSpriteFont(BaseTexture* texture, SpriteFontGlyph** glyphs, int charactersCount);

    sf::Font* innerImpl;
private:

};