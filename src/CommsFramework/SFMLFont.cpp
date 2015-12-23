#include "SFMLFont.h"

SFMLFont::SFMLFont()
{
    innerImpl = new sf::Font();
}


SFMLFont::~SFMLFont()
{
}

void SFMLFont::Load(std::string path)
{
    bool res = innerImpl->loadFromFile(path);

}