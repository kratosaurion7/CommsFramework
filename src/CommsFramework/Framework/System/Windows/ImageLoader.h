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

class ImageLoader
{
public:
    ImageLoader();
    ~ImageLoader();

    IWICBitmap* LoadImageFromDisk(std::string fileName);
    
    IWICBitmap* LoadDirect2DImage(std::string fileName);

    IWICBitmap* CreateBitmap(TgaFile* originTga, bool supportAlpha = true);

    void SaveToPng(TgaFile* file, std::string destinationFilename);
    void SaveToPng(IWICBitmap* bmp, std::string destinationFilename);

private:
    IWICImagingFactory* WicFactory;



    void InitializeServices();
};

#endif