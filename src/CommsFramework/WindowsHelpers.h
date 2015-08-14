#pragma once

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>

#include <string>

std::wstring CStringToWideString(std::string cstr);

std::string WideStringToCString(std::wstring wstr);
