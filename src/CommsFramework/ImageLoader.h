#pragma once

#ifdef WIN32

#include <Windows.h>
#include <d2d1.h>

#include <wincodec.h>
#include <wincodecsdk.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")


#include <string>

#endif

class ImageLoader
{
public:
    ImageLoader();
    ~ImageLoader();

    IWICBitmapFrameDecode* LoadImage(std::string fileName);

private:
#ifdef WIN32
    IWICImagingFactory* WicFactory;



#endif

    void InitializeServices();
};

