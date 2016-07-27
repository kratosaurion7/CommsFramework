#include "ImageLoader.h"

#include "WindowsHelpers.h"

ImageLoader::ImageLoader()
{
#ifdef WIN32
    WicFactory = NULL;


#endif
    
    InitializeServices();

}


ImageLoader::~ImageLoader()
{
}

IWICBitmapFrameDecode* ImageLoader::LoadImage(std::string fileName)
{
    IWICBitmapDecoder* decoder = NULL;

    wchar_t name = (wchar_t)CStringToWideString(fileName).c_str();

    HRESULT hr;
    
    hr = WicFactory->CreateDecoderFromFilename(&name, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

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
#ifdef WIN32
    CoInitialize(NULL);

    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&WicFactory)
    );
#endif
}
