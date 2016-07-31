#pragma once

class TgaFile;

#ifdef _WIN32

#include <Windows.h>
#include "WindowsHelpers.h"

extern HANDLE outMut;

// Quick Window
#define MAX_QUICKWINDOWS 10

extern HINSTANCE qk_inst;
extern HWND qk_hwnd[MAX_QUICKWINDOWS];
extern HANDLE qk_threads[MAX_QUICKWINDOWS];
extern DWORD qk_threadid[MAX_QUICKWINDOWS];

BOOL InitApp();
LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
int GetNCmdShow();

DWORD WINAPI ThreadFuncHandleWindows(LPVOID lpParam);

int GetNextFreeHwndIndex();


#endif // _WIN32

void QuickCreateWindow(TgaFile* content);

void CloseQuickWindow();