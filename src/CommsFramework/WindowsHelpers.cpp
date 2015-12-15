#include "WindowsHelpers.h"

std::wstring CStringToWideString(std::string cstr)
{
    wchar_t* wText = new wchar_t[cstr.length() + 1];
    mbstowcs(wText, cstr.c_str(), cstr.length() + 1);

    std::wstring out = wText;
    delete[] wText;

    return out;
}

std::string WideStringToCString(std::wstring wstr)
{
    char* cText = new char[wstr.length() + 1];
    wcstombs(cText, wstr.c_str(), wstr.length() + 1);

    std::string out = cText;
    delete[] cText;

    return out;
}