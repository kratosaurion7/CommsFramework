#include "WindowsHelpers.h"

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>


std::wstring CStringToWideString(std::string cstr)
{
    wchar_t* wText = new wchar_t[cstr.length() + 1];
    std::size_t ret = mbstowcs(wText, cstr.c_str(), cstr.length() + 1);

    std::wstring out = std::wstring(wText);
    delete[] wText;

    return out;
}

std::string WideStringToCString(std::wstring wstr)
{
    char* cText = new char[wstr.length() + 1];
    std::size_t ret = wcstombs(cText, wstr.c_str(), wstr.length() + 1);

    std::string out = std::string(cText);
    delete[] cText;

    return out;
}