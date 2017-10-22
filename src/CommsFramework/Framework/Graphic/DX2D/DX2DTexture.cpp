#ifdef WIN32
#include "DX2DTexture.h"

#include "DX2DGraphicEngine.h"
#include "System/Windows/ImageLoader.h"

DX2DTexture::DX2DTexture()
{
    texture = NULL;
    Graphics = NULL;
    
    Width = 0;
    Height = 0;
}

DX2DTexture::~DX2DTexture()
{
    if(texture != NULL)
        texture->Release();
}

void DX2DTexture::Initalize(float width, float height)
{
    Width = width;
    Height = height;
}

int DX2DTexture::Load(std::string path)
{
    ImageLoader* loader = Graphics->Loader;
    
    IWICBitmapSource* image = loader->LoadDirect2DImage(path);
    
    texture = image;

    return 0;
}

void DX2DTexture::LoadFromMemory(char* data, int dataSize)
{
}

FSize DX2DTexture::GetSize()
{
    UINT w = 0;
    UINT h = 0;
    
    HRESULT hr = texture->GetSize(&w, &h);
    assert(hr == S_OK);
    
    return FSize((float)h, (float)w);
}

BaseTexture* DX2DTexture::GetSubTexture(FRectangle rec)
{
    return NULL;
}

void DX2DTexture::SetSolidColor(uint32_t pixelColor)
{
}

void DX2DTexture::SaveTextureToFile()
{
}

void DX2DTexture::SaveTextureToFile(std::string fileName)
{
}

void DX2DTexture::OverlayTexture(BaseTexture* other)
{
}

#endif