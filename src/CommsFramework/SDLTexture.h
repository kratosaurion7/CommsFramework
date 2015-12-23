#pragma once

#include <string>
#include <cstdint>

#include "FSize.h"

#include "BaseTexture.h"

class SDLTexture : public BaseTexture
{
public:
    SDLTexture();
    ~SDLTexture();

    virtual void Initalize(float width, float height);

    virtual void Load(std::string path);

    virtual void LoadFromMemory(char* data, int dataSize);

    virtual FSize GetSize();

    virtual void SetSolidColor(uint32_t pixelColor);
};

