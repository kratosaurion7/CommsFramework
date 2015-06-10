#include "DTexture.h"

#include <SFML\Graphics.hpp>

DTexture::DTexture()
{
    innerImpl = new sf::Texture();
}


DTexture::~DTexture()
{
	delete innerImpl;
}
