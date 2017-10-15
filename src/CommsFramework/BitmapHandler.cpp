#include "BitmapHandler.h"

#ifdef WIN32

#include "WindowsHelpers.h"

BITMAPINFO* CreateEmptyBitmap()
{
    HBITMAP testbitmap = (HBITMAP)LoadImage(NULL, L"Untitled.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    int err = GetLastError();

    SIZE siz;
    BOOL res = GetBitmapDimensionEx(testbitmap, &siz);

    auto err2 = GetLastErrorString();

    tagBITMAPFILEHEADER* hdr;
    tagBITMAPINFOHEADER* inf;
    
    

    return nullptr;
}

#endif