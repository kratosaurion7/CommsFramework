#pragma once

#include "TgaFile.h"

#ifdef _WIN32

#include <Windows.h>
#include "WindowsHelpers.h"

#define MAX_QUICKWINDOWS 10

// Thread & Window handling arrays

struct QuickWindowCreateThreadOptions
{
    int ThreadIndex;
    LPCWSTR WindowName;
    TgaFile* WindowContent;
};

// Window init functions and window callback
BOOL InitApp();
BOOL InitDX();
int GetNCmdShow();
LRESULT CALLBACK QuickWindowProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI ThreadFuncHandleWindows(LPVOID lpParam);

void DoPaint(HWND window);

// Finds the next available spot in the window array
int GetNextFreeHwndIndex();
int GetIndexByHwnd(HWND window);

void DeleteQuickWindowResources(HWND window);

#endif

int QuickCreateWindow(TgaFile* content);

void CloseQuickWindow(int windowIndex);