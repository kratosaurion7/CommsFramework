#include "DTexture.h"

#include <SFML\System\Vector2.hpp>

#include <SFML\Graphics.hpp>

DTexture::DTexture()
{
    innerImpl = new sf::Texture();
	innerImpl->setSmooth(false);
}


DTexture::~DTexture()
{
	delete innerImpl;
}

void DTexture::Load(std::string path)
{
	bool res = innerImpl->loadFromFile(path);

	if (res)
	{
		sf::Vector2u vec = innerImpl->getSize();

		FSize* mySize = new FSize(vec.y, vec.x);

		size = mySize;
	}
}

FSize* DTexture::GetSize()
{
	return size;
}
