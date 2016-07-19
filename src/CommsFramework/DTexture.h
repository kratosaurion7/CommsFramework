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

    virtual BaseTexture* GetSubTexture(FRectangle rec);

    virtual FSize GetSize();

    virtual void SetSolidColor(uint32_t pixelColor);

    virtual void SaveTextureToFile();
    virtual void SaveTextureToFile(std::string fileName);

    virtual void OverlayTexture(BaseTexture* other);

    sf::Texture* innerImpl;

private:
    FSize size;

};