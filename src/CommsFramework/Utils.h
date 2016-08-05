#pragma once

class TgaFile;

#ifdef _WIN32

#include <Windows.h>
#include "WindowsHelpers.h"

extern HANDLE outMut;

// ===== Quick Window =====
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

// ===== Quick Window =====

#endif // _WIN32

void QuickCreateWindow(TgaFile* content);

void CloseQuickWindow();