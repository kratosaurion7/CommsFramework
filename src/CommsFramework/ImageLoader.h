#pragma once

class TgaFile;

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

    IWICBitmap* CreateBitmap(TgaFile* originTga, bool supportAlpha = true);

    void SaveToPng(TgaFile* file);
    void SaveToPng(IWICBitmap* bmp);

private:
    IWICImagingFactory* WicFactory;



    void InitializeServices();
};

