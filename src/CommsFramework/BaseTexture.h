#pragma once

class FSize;

#include <cstdint>

#include <string>

#include "FSize.h"
#include "FRectangle.h"

class BaseTexture
{
public:
    virtual void Initalize(float width, float height) = 0;

    virtual void Load(std::string path) = 0;

    virtual void LoadFromMemory(char* data, int dataSize) = 0;

    virtual FSize GetSize() = 0;

    virtual BaseTexture* GetSubTexture(FRectangle rec) = 0;

    virtual void SetSolidColor(uint32_t pixelColor) = 0;

    std::string TexturePath;
};