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
    DX2DTextureLoader* loader = Graphics->Loader;
    
    IWICBitmap* image = loader->LoadFromDisk(path);

    this->texture = loader->CreateD2DXBitmap(image);
    
    return 0;
}

void DX2DTexture::LoadFromMemory(char* data, int dataSize)
{
}

FSize DX2DTexture::GetSize()
{
    if (texture == NULL)
    {
        return FSize(0, 0);
    }
    
    D2D1_SIZE_F size = texture->GetSize();
    
    return FSize((float)size.height, (float)size.width);
}

BaseTexture* DX2DTexture::GetSubTexture(FRectangle rec)
{
    return NULL;
}

void DX2DTexture::SetSolidColor(uint32_t pixelColor)
{
    HRESULT hr;
    IWICBitmap* bitmap = this->Graphics->Loader->CreateEmptyBitmap(this->Width, this->Height);

    WICRect r;
    r.X = 0;
    r.Y = 0;
    r.Width = (INT)this->Width;
    r.Height = (INT)this->Height;

    IWICBitmapLock* lk;
    hr = bitmap->Lock(&r, WICBitmapLockWrite, &lk);

    UINT bufSize = 0;
    UINT stride = 0;
    BYTE* bits = NULL;
    hr = lk->GetStride(&stride);

    hr = lk->GetDataPointer(&bufSize, &bits);

    for (UINT i = 0; i < bufSize; i)
    {
        // Format is GUID_WICPixelFormat32bppPBGRA
        BYTE a = (pixelColor & 0xFF000000) >> 24;
        BYTE r = (pixelColor & 0x00FF0000) >> 16;
        BYTE g = (pixelColor & 0x0000FF00) >> 8;
        BYTE b = (pixelColor & 0x000000FF);
        
        bits[i++] = static_cast<BYTE>(b);
        bits[i++] = static_cast<BYTE>(g);
        bits[i++] = static_cast<BYTE>(r);
        bits[i++] = static_cast<BYTE>(a);
    }

    lk->Release();

    this->texture = this->Graphics->Loader->CreateD2DXBitmap(bitmap);
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