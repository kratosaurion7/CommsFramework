#include "ImageLoader.h"

#include "WindowsHelpers.h"

ImageLoader::ImageLoader()
{
    WicFactory = NULL;
    
    InitializeServices();

}


ImageLoader::~ImageLoader()
{
}

IWICBitmapFrameDecode* ImageLoader::LoadImageFromDisk(std::string fileName)
{
    IWICBitmapDecoder* decoder = NULL;

    std::wstring stemp = std::wstring(fileName.begin(), fileName.end());
    LPCWSTR sw = stemp.c_str();

    HRESULT hr;
    
    hr = WicFactory->CreateDecoderFromFilename(sw, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

    if (FAILED(hr))
    {
        std::string errorString = GetLastErrorString();

        return NULL;
    }

    IWICBitmapFrameDecode *frame = NULL;

    if (SUCCEEDED(hr))
    {
        hr = decoder->GetFrame(0, &frame);
    }
    else
    {
        std::string errorString = GetLastErrorString();

        return NULL;
    }

    return frame;
}

void ImageLoader::InitializeServices()
{
    CoInitialize(NULL);

    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&WicFactory)
    );
}
