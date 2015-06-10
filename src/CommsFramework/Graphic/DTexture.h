#pragma once

#include <SFML\Graphics.hpp>

class DTexture
{
public:
    DTexture();
    ~DTexture();

private:
    sf::Texture* innerImpl;
};

