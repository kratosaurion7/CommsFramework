#include "SFMLFont.h"

SFMLFont::SFMLFont()
{
    innerImpl = new sf::Font();
}


SFMLFont::~SFMLFont()
{
}

void SFMLFont::LoadFontFile(std::string path)
{
    bool res = innerImpl->loadFromFile(path);

    FontType = FONT_FILE;
}