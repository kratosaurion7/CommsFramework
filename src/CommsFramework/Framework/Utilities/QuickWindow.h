#pragma once

/** QuickWindow is an encapsulated window that is used to show an image.
 * 
 * USAGE :
 *  To use the QuickWindow, the caller needs to supply a pointer of TgaFile and call QuickCreateWindow
 *  The creation functions returns an integer index that is used to close the window. Closing the 
 *  window is done by calling CloseQuickWindow and passing the index.
 * 
 * DEPENDS :
 *  - Win32
 *  - Direct2D
 *  - Windows Imaging Components
 *  - TgaFile
 *
 * SPECS :
 *  - Each window is handled by a separate thread.
 *  - A maximum of MAX_QUICKWINDOWS (10) windows can be opened at one time.
 *  - On Windows, the QuickWindows are handled by DirectD2 
 * 


*/

#include "TgaFile.h"

#ifdef WIN32

#include <Windows.h>
#include "WindowsHelpers.h"

#define MAX_QUICKWINDOWS 10

// Thread & Window handling arrays

// Structure passed to the thread operating the window.
struct QuickWindowCreateThreadOptions
{
    int ThreadIndex;
    LPCWSTR WindowName;
    TgaFile* WindowContent;
};

// Window init functions and window callback
BOOL InitApp();
BOOL InitDX();
/** Function used to get the command for the window show.
*
* This is needed when the QuickWindow is used from a project that is not a Windows Subsystem.
* For example from a Console project. */
int GetNCmdShow();
LRESULT CALLBACK QuickWindowProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI ThreadFuncHandleWindows(LPVOID lpParam);

void DoPaint(HWND window);

// Finds the next available spot in the window array
int GetNextFreeHwndIndex();
int GetIndexByHwnd(HWND window);

// Implements the deletes and release of the resources of a window.
void DeleteQuickWindowResources(HWND window);

#endif

int QuickCreateWindow(TgaFile* content);

void CloseQuickWindow(int windowIndex);