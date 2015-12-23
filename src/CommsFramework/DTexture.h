#pragma once

#include <string>
#include <cstdint>

#include <SFML\Graphics.hpp>
#include "FSize.h"
#include "BaseTexture.h"

class DTexture : public BaseTexture
{
public:
    DTexture();
    ~DTexture();

    virtual void Initalize(float width, float height);

    void Load(std::string path);

    virtual void LoadFromMemory(char* data, int dataSize);

    virtual FSize GetSize();

    virtual void SetSolidColor(uint32_t pixelColor);

    sf::Texture* innerImpl;

private:
    FSize size;

};