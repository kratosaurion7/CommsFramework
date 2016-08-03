#include "ImageLoader.h"

#include "TgaFile.h"
#include "WindowsHelpers.h"

ImageLoader::ImageLoader()
{
    WicFactory = NULL;
    
    InitializeServices();

}


ImageLoader::~ImageLoader()
{
}

IWICBitmap* ImageLoader::LoadImageFromDisk(std::string fileName)
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

    IWICBitmap* bitmap = NULL;
    hr = WicFactory->CreateBitmapFromSource(frame, WICBitmapCacheOnDemand, &bitmap);

    return bitmap;
}

IWICBitmap* ImageLoader::CreateBits(TgaFile* originTga)
{
    HRESULT hr;

    // Extract bytes of color
    unsigned char* imageData = new unsigned char[256 * 256 * 32];
    int index = 0;
    for (int i = 0; i < originTga->Height; i++)
    {
        for (int j = 0; j < originTga->Width; j++)
        {
            TgaPix* x = originTga->Get(i, j);

            memcpy(&imageData[index++], &x->b, sizeof(unsigned char));
            memcpy(&imageData[index++], &x->g, sizeof(unsigned char));
            memcpy(&imageData[index++], &x->r, sizeof(unsigned char));
            memcpy(&imageData[index++], &x->a, sizeof(unsigned char));
        }
    }



    IWICBitmap* bitmap = NULL;
    hr = WicFactory->CreateBitmap(originTga->Width, originTga->Height, GUID_WICPixelFormat32bppBGRA, WICBitmapCacheOnDemand, &bitmap);

    WICRect rec;
    rec.Height = originTga->Height;
    rec.Width = originTga->Width;
    rec.X = 0;
    rec.Y = 0;

    IWICBitmapLock* lock = NULL;
    hr = bitmap->Lock(&rec, WICBitmapLockWrite, &lock);
    
    UINT bufSize = 0;
    UINT stride = 0;
    BYTE* bits = NULL;

    hr = lock->GetStride(&stride);

    hr = lock->GetDataPointer(&bufSize, &bits);

    unsigned char* bytes = imageData;

    for (UINT i = 0; i < bufSize; i++)
    {
        bits[i] = static_cast<BYTE>(bytes[i]);
    }


    //ZeroMemory(bits, bufSize);

    lock->Release();

    IWICBitmapEncoder* enc = NULL;
    IWICBitmapFrameEncode* frame = NULL;
    IPropertyBag2 *pPropertybag = NULL;
    IWICStream* bitmapStream = NULL;

    hr = WicFactory->CreateStream(&bitmapStream);
    
    DeleteFile(L"out.png");
    hr = bitmapStream->InitializeFromFilename(L"out.png", GENERIC_WRITE);

    hr = WicFactory->CreateEncoder(GUID_ContainerFormatPng, NULL, &enc);
    
    hr = enc->Initialize(bitmapStream, WICBitmapEncoderNoCache);

    hr = enc->CreateNewFrame(&frame, &pPropertybag);

    //PROPBAG2 option = { 0 };
    //option.pstrName = L"TiffCompressionMethod";
    //VARIANT varValue;
    //VariantInit(&varValue);
    //varValue.vt = VT_UI1;
    //varValue.bVal = WICTiffCompressionZIP;
    //hr = pPropertybag->Write(1, &option, &varValue);

    hr = frame->Initialize(pPropertybag);
    hr = frame->SetSize(originTga->Width, originTga->Height);
    WICPixelFormatGUID formatGUID = GUID_WICPixelFormat32bppBGRA;
    hr = frame->SetPixelFormat(&formatGUID);
    
    hr = IsEqualGUID(formatGUID, GUID_WICPixelFormat32bppBGRA) ? S_OK : E_FAIL;
    
    //UINT cbStride = (originTga->Width * 24 + 7) / 8/***WICGetStride***/;
    UINT cbStride = (originTga->Width * 32) / 8/***WICGetStride***/;
    UINT cbBufferSize = originTga->Height * cbStride;

    BYTE *pbBuffer = new BYTE[cbBufferSize];

    if (pbBuffer != NULL)
    {
        unsigned char* bytes = imageData;

        for (UINT i = 0; i < cbBufferSize; i++)
        {
            pbBuffer[i] = static_cast<BYTE>(bytes[i]);
        }

        hr = frame->WritePixels(originTga->Height, cbStride, cbBufferSize, pbBuffer);

        delete[] pbBuffer;
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }

    hr = frame->Commit();
    hr = enc->Commit();

    auto err = GetLastErrorString();

    return bitmap;
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
