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

    IWICImagingFactory* factory = this->Graphics->Loader->GetFactory();

    IWICBitmap* outBitmap = NULL;

    /*D2D1_SIZE_U rec;
    rec.height = height;
    rec.width = width;

    D2D1_BITMAP_PROPERTIES prop;
    
    ID2D1Bitmap* outBitmap;
    HRESULT hr = Graphics->RenderTarget->CreateBitmap(rec, D2D1::BitmapProperties(), &outBitmap);
*/
    

    //HRESULT hr = factory->CreateBitmap((UINT)width, (UINT)height, GUID_WICPixelFormat32bppRGBA, WICBitmapCacheOnDemand, &outBitmap);
    HRESULT hr = factory->CreateBitmap((UINT)width, (UINT)height, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnDemand, &outBitmap);

    this->texture = outBitmap;
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
    IWICImagingFactory* factory = this->Graphics->Loader->GetFactory();

    IWICBitmap* bitmap;
    HRESULT hr = factory->CreateBitmapFromSource(this->texture, WICBitmapNoCache, &bitmap);

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