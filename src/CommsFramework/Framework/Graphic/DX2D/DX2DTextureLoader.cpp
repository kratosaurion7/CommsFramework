#ifdef WIN32
#include "DX2DTextureLoader.h"

#include <stdio.h>

#include "Filesystem/Windows/WindowsHelpers.h"

DX2DTextureLoader::DX2DTextureLoader(IWICImagingFactory* wicFactory, ID2D1HwndRenderTarget* renderTarget)
{
    factory = wicFactory;
    renderer = renderTarget;
}

DX2DTextureLoader::~DX2DTextureLoader()
{
    factory = NULL;
    renderer = NULL;
}

IWICBitmap* DX2DTextureLoader::CreateEmptyBitmap(int w, int h)
{
    IWICBitmap* result;
    HRESULT hr = factory->CreateBitmap(w, h, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnDemand, &result);

    if (FAILED(hr))
    {
        std::string errorString = GetLastErrorString();

        printf(errorString.c_str());

        return NULL;
    }

    return result;
}

IWICBitmap* DX2DTextureLoader::LoadFromDisk(std::string path)
{
    HRESULT hr;
    
    IWICBitmapDecoder* decoder = NULL;
    std::wstring wpath = CStringToWideString(path);
    
    hr = factory->CreateDecoderFromFilename(wpath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
    
    if(FAILED(hr))
    {
        std::string errorString = GetLastErrorString();
        
        printf(errorString.c_str());
        
        return NULL;
    }
    
    IWICBitmapFrameDecode* frame = NULL;
    
    hr = decoder->GetFrame(0, &frame);
    
    if(FAILED(hr))
    {
        std::string errorString = GetLastErrorString();
        
        printf(errorString.c_str());
        
        decoder->Release();
        
        return NULL;
    }
    
    IWICBitmap* bitmap = NULL;
    
    hr = factory->CreateBitmapFromSource(frame, WICBitmapCacheOnDemand, &bitmap);
    
    if(FAILED(hr))
    {
        std::string errorString = GetLastErrorString();
        
        printf(errorString.c_str());
        
        frame->Release();
        decoder->Release();
        
        return NULL;
    }

    frame->Release();
    decoder->Release();

    return bitmap;
}

IWICBitmap* DX2DTextureLoader::ConvertTextureFormat(IWICBitmap* bitmap, REFWICPixelFormatGUID newFormat)
{
    HRESULT hr;
    IWICFormatConverter* converter = NULL;
    
    hr = factory->CreateFormatConverter(&converter);
    
    if(FAILED(hr))
    {
        std::string errorString = GetLastErrorString();
        
        printf(errorString.c_str());

        return NULL;
    }
    
    WICPixelFormatGUID oldFormat;

    hr = bitmap->GetPixelFormat(&oldFormat);

    if (FAILED(hr))
    {
        std::string errorString = GetLastErrorString();

        printf(errorString.c_str());

        converter->Release();

        return NULL;
    }

    BOOL result;
    hr = converter->CanConvert(oldFormat, newFormat, &result);
    
    if(FAILED(hr))
    {
        std::string errorString = GetLastErrorString();
        
        printf(errorString.c_str());
        
        converter->Release();
        
        return NULL;
    }
    
    if(result == FALSE)
    {
        printf("Cannot convert pixel format.");
        
        converter->Release();
        
        return NULL;
    }
    
    hr = converter->Initialize(
        bitmap, newFormat,
        WICBitmapDitherTypeNone, nullptr, 0.f,
        WICBitmapPaletteTypeMedianCut);
        
    if(FAILED(hr))
    {
        std::string errorString = GetLastErrorString();
        
        printf(errorString.c_str());
        
        converter->Release();
        
        return NULL;
    }
    
    IWICBitmap* newBitmap = NULL;
    
    hr = factory->CreateBitmapFromSource(converter, WICBitmapCacheOnDemand, &newBitmap);
    
    if(FAILED(hr))
    {
        std::string errorString = GetLastErrorString();
        
        printf(errorString.c_str());
        
        converter->Release();
        
        return NULL;
    }
    // TODO : Discard old bitmap ?
    return newBitmap;
}

ID2D1Bitmap* DX2DTextureLoader::CreateD2DXBitmap(IWICBitmap* bitmap)
{
    IWICBitmap* converted = NULL;
    converted = this->ConvertTextureFormat(bitmap, GUID_WICPixelFormat32bppPBGRA);

    ID2D1Bitmap* bits = NULL;
    HRESULT hr = renderer->CreateBitmapFromWicBitmap(converted, &bits);

    if(FAILED(hr))
    {
        std::string errorString = GetLastErrorString();
        
        printf(errorString.c_str());
        
        return NULL;
    }

    return bits;
}

ID2D1Bitmap* DX2DTextureLoader::ConvertDXTextureFormat(ID2D1Bitmap* bitmap, REFWICPixelFormatGUID newFormat)
{
    return NULL;
}

std::string DX2DTextureLoader::GetTextureFormatName(IWICBitmap* bitmap)
{
    return "";
}

std::string DX2DTextureLoader::GetTextureFormatName(ID2D1Bitmap* bitmap)
{
    return "";
}


#endif