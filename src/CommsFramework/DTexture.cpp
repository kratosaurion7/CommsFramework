#include "DTexture.h"

#include <cassert>

#include <SFML\System\Vector2.hpp>
#include "Utilities.h"


DTexture::DTexture()
{
    innerImpl = new sf::Texture();
    innerImpl->setSmooth(false);
}

DTexture::~DTexture()
{
    if (innerImpl != NULL)
        delete innerImpl;
}

void DTexture::Initalize(float width, float height)
{
    size.Height = height;
    size.Width = width;
}

void DTexture::Load(std::string path)
{
    bool res = innerImpl->loadFromFile(path);

    if (res)
    {
        sf::Vector2u vec = innerImpl->getSize();

        size.Height = vec.y;
        size.Width = vec.x;

        TexturePath = path;
    }
}

void DTexture::LoadFromMemory(char * data, int dataSize)
{
    bool res = innerImpl->loadFromMemory(data, dataSize);

    if (res)
    {
        sf::Vector2u vec = innerImpl->getSize();

        size.Height = vec.y;
        size.Width = vec.x;
    }
}

FSize DTexture::GetSize()
{
    return size;
}

void DTexture::SetSolidColor(uint32_t pixelColor)
{
    sf::Image* image = new sf::Image();
    image->create(size.Width, size.Height, sf::Color(pixelColor));

    innerImpl->loadFromImage((*image)); // Should declare the image as stack local ?
}