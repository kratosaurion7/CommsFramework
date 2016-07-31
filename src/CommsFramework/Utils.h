#pragma once

class TgaFile;

#ifdef _WIN32

#include <Windows.h>
#include "WindowsHelpers.h"

extern HANDLE outMut;

// ===== Quick Window =====
#define MAX_QUICKWINDOWS 10

// Thread & Window handling arrays
//extern HINSTANCE qk_inst;
//extern HWND qk_hwnd[MAX_QUICKWINDOWS];
//extern HANDLE qk_threads[MAX_QUICKWINDOWS];
//extern DWORD qk_threadid[MAX_QUICKWINDOWS];

// Window init functions and window callback
BOOL InitApp();
BOOL InitDX();
int GetNCmdShow();
LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI ThreadFuncHandleWindows(LPVOID lpParam);

void DoPaint(HWND window);

// Finds the next available spot in the window array
int GetNextFreeHwndIndex();
int GetIndexByHwnd(HWND window);


#endif // _WIN32

void QuickCreateWindow(TgaFile* content);

void CloseQuickWindow();