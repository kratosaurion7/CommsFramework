#include "WindowsHelpers.h"

#ifdef WIN32

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>


std::wstring CStringToWideString(std::string cstr)
{
    std::wstring stemp = std::wstring(cstr.begin(), cstr.end());
    
    return stemp;
}

std::string WideStringToCString(std::wstring wstr)
{
    std::string stemp = std::string(wstr.begin(), wstr.end());

    return stemp;
}

std::string GetLastErrorString()
{
    DWORD err = GetLastError();

    wchar_t errorBuf[512];

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, err, 0, errorBuf, 512, NULL);

    return WideStringToCString(errorBuf);
}

#endif