#pragma once

class TgaFile;

#ifdef WIN32

#include <Windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <wincodecsdk.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

#include <string>

/*
 * Pixel formats https://msdn.microsoft.com/en-us/library/windows/desktop/ee719797(v=vs.85).aspx
 */

class ImageLoader
{
public:
    ImageLoader();
    ~ImageLoader();

    IWICBitmapSource* LoadImageFromDisk(std::string fileName);
    
    IWICBitmapSource* LoadDirect2DImage(std::string fileName);

    IWICBitmap* CreateBitmap(TgaFile* originTga, bool supportAlpha = true);

    void SaveToPng(TgaFile* file, std::string destinationFilename);
    void SaveToPng(IWICBitmap* bmp, std::string destinationFilename);

    IWICImagingFactory* GetFactory();

private:
    IWICImagingFactory* WicFactory;



    void InitializeServices();
};

#endif