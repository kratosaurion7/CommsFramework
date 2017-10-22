#pragma once

class DX2DGraphicEngine;

#include <string>
#include <cstdint>

#include <Windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <wincodecsdk.h>

#include "Geometry/FSize.h"
#include "Graphic/Base Classes/BaseTexture.h"

class DX2DTexture : public BaseTexture
{
public:
    IWICBitmapSource* texture;
    
    DX2DGraphicEngine* Graphics;
    
    float Width;
    float Height;
    
    DX2DTexture();
    ~DX2DTexture();
    
    virtual void Initalize(float width, float height);
    
    virtual int Load(std::string path);

    virtual void LoadFromMemory(char* data, int dataSize);

    virtual FSize GetSize();
    
    virtual BaseTexture* GetSubTexture(FRectangle rec);

    virtual void SetSolidColor(uint32_t pixelColor);

    virtual void SaveTextureToFile();
    virtual void SaveTextureToFile(std::string fileName);

    virtual void OverlayTexture(BaseTexture* other);
    
private:
    
};