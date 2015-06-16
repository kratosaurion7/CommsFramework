#include "DTexture.h"

#include <SFML\System\Vector2.hpp>

#include <SFML\Graphics.hpp>

#include <cstdint>


DTexture::DTexture()
{
    innerImpl = new sf::Texture();
	innerImpl->setSmooth(false);
}


DTexture::~DTexture()
{
	if(innerImpl != NULL)
		delete innerImpl;

	if(size != NULL)
		delete size;
}

void DTexture::Initalize(int width, int height)
{
	FSize* mySize = new FSize();

	mySize->Height = height;
	mySize->Width = width;

	size = mySize;
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

void DTexture::SetSolidColor(uint32_t pixelColor)
{
	sf::Image* image = new sf::Image();
	image->create(size->Width, size->Height, sf::Color(pixelColor));

	innerImpl->loadFromImage((*image)); // Should declare the image as stack local ?
}
