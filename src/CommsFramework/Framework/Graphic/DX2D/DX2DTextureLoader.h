#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <wincodecsdk.h>

#include <string>

/*
 * Pixel formats https://msdn.microsoft.com/en-us/library/windows/desktop/ee719797(v=vs.85).aspx
 */

class DX2DTextureLoader
{
public:
    DX2DTextureLoader(IWICImagingFactory* wicFactory, ID2D1HwndRenderTarget* renderTarget);
    ~DX2DTextureLoader();

    IWICBitmap* CreateEmptyBitmap(int w, int h);
    
    IWICBitmap* LoadFromDisk(std::string path);
    
    IWICBitmap* ConvertTextureFormat(IWICBitmap* bitmap, REFWICPixelFormatGUID newFormat);
    
    ID2D1Bitmap* CreateD2DXBitmap(IWICBitmap* bitmap);
    
    ID2D1Bitmap* ConvertDXTextureFormat(ID2D1Bitmap* bitmap, REFWICPixelFormatGUID newFormat);
    
    std::string GetTextureFormatName(IWICBitmap* bitmap);
    
    std::string GetTextureFormatName(ID2D1Bitmap* bitmap);
    
private:
    ID2D1HwndRenderTarget* renderer;
    
    IWICImagingFactory* factory;
};