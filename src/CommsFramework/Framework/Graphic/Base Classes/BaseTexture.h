#pragma once

class FSize;
class BaseGraphicEngine;

#include <cstdint>
#include <string>

#include "Geometry/FSize.h"
#include "Geometry/FRectangle.h"

class BaseTexture
{
public:
    virtual ~BaseTexture() = 0;

    std::string TexturePath;

    std::string TextureName;

    BaseGraphicEngine* Engine;

    virtual void Initalize(float width, float height) = 0;

    virtual int Load(std::string path) = 0;

    virtual void LoadFromMemory(char* data, int dataSize) = 0;

    virtual FSize GetSize() = 0;

    virtual BaseTexture* GetSubTexture(FRectangle rec) = 0;

    virtual void SetSolidColor(uint32_t pixelColor) = 0;

    virtual void SaveTextureToFile() = 0;
    virtual void SaveTextureToFile(std::string fileName) = 0;

    virtual void OverlayTexture(BaseTexture* other) = 0;
};

inline BaseTexture::~BaseTexture() { };