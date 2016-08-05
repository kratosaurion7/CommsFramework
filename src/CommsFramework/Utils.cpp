#include "Utils.h"

#include <cassert>

#include "TgaFile.h"
#include "ImageLoader.h"

void stprintf(char* buf)
{
};


#ifdef _WIN32

#include <d2d1.h>
#include <wincodec.h>
#include <wincodecsdk.h>
#pragma comment(lib, "d2d1.lib")


HANDLE outMut;

HINSTANCE qk_inst;
HWND qk_hwnd[MAX_QUICKWINDOWS] = { 0 };
HANDLE qk_threads[MAX_QUICKWINDOWS] = { 0 };
DWORD qk_threadid[MAX_QUICKWINDOWS] = { 0 };

// ===== DirectX =====
ID2D1Factory* D2Factory = NULL;
ID2D1HwndRenderTarget* RenderTarget[MAX_QUICKWINDOWS] = { 0 };
ID2D1BitmapBrush* BGBrush[MAX_QUICKWINDOWS] = { 0 };

BOOL InitApp()
{
    WNDCLASS wc;

    wc.style = 0;
    wc.lpfnWndProc = QuickWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = qk_inst;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("CommsFramework");

    if (!RegisterClass(&wc)) return FALSE;

    return TRUE;
}

BOOL InitDX()
{
    HRESULT hr = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &D2Factory
    );

    return SUCCEEDED(hr);
}

LRESULT CALLBACK QuickWindowProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            DoPaint(hwnd);

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:
        {
            //PostQuitMessage(0);

			int windowIndex = GetIndexByHwnd(hwnd);
			qk_hwnd[windowIndex] = 0; // TODO : Need to CloseHandle() ?
			qk_threadid[windowIndex] = 0;
           
			break;
        }
        default:
        {
            return DefWindowProc(hwnd, uiMsg, wParam, lParam);
        }
    }

    return 0;
}

int GetNCmdShow()
{
    STARTUPINFO startupInfo;
    GetStartupInfo(&startupInfo);
    if ((startupInfo.dwFlags & STARTF_USESHOWWINDOW) != 0) {
        return startupInfo.wShowWindow;
    }
    return SW_SHOWDEFAULT;
}

DWORD WINAPI ThreadFuncHandleWindows(LPVOID lpParam)
{
	QuickWindowCreateThreadOptions* threadStartParams = (QuickWindowCreateThreadOptions*)lpParam;

	int qkIndex = threadStartParams->ThreadIndex;
	TgaFile* content = threadStartParams->WindowContent;

	HWND hwnd = CreateWindow(
		L"CommsFramework",
		threadStartParams->WindowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		content->Width, content->Height,
		NULL,
		NULL,
		qk_inst,
		0);

	qk_hwnd[qkIndex] = hwnd;

	RECT rec;
	GetClientRect(hwnd, &rec);

	HRESULT hr = D2Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hwnd,
			D2D1::SizeU(
				rec.right - rec.left,
				rec.bottom - rec.top)
		),
		&RenderTarget[qkIndex]);

	ImageLoader loader = ImageLoader();
	IWICBitmap* bmp = loader.CreateBitmap(content, false);

	ID2D1Bitmap* d2bmp;
	hr = RenderTarget[qkIndex]->CreateBitmapFromWicBitmap(bmp, &d2bmp);
	hr = RenderTarget[qkIndex]->CreateBitmapBrush(d2bmp, &BGBrush[qkIndex]);

	bmp->Release();

	ShowWindow(hwnd, GetNCmdShow());
	UpdateWindow(hwnd);

    MSG msg;
	BOOL bRet;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
			return 1;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

    return 0;
}

void DoPaint(HWND window)
{
    int myIndex = GetIndexByHwnd(window);

	if (myIndex < 0)
	{
		fprintf(stderr, "Window cannot be found in the array.");
		return;
	}

    ID2D1HwndRenderTarget* target = RenderTarget[myIndex];
    ID2D1BitmapBrush* brush = BGBrush[myIndex];

    if (target == NULL || brush == NULL)
        return;

    RECT rc;
    GetClientRect(window, &rc);

    target->BeginDraw();

    target->Clear();
    target->FillRectangle(
        D2D1::RectF(
            rc.left,
            rc.top,
            rc.right,
            rc.bottom),
        brush);

    HRESULT hr = target->EndDraw();
}

int GetNextFreeHwndIndex()
{
    for (int i = 0; i < MAX_QUICKWINDOWS; i++)
    {
        if (qk_threads[i] == NULL)
            return i;
    }

    return -1;
}

int GetIndexByHwnd(HWND window)
{
    for (int i = 0; i < MAX_QUICKWINDOWS; i++)
    {
        if (qk_hwnd[i] == window)
            return i;
    }

    return -1;
}

void QuickCreateWindow(TgaFile* content)
{
    if (qk_inst == NULL)
    {
        qk_inst = GetModuleHandle(nullptr);

        if (!InitApp()) return;
        if (!InitDX()) return;
    }

    int index = GetNextFreeHwndIndex();
	if (index < 0)
	{
		fprintf(stderr, "Max number of QuickWindow has been reached (10). Cannot create any more.");
        return;
	}

	QuickWindowCreateThreadOptions* threadOpts = new QuickWindowCreateThreadOptions();
	threadOpts->ThreadIndex = index;
	threadOpts->WindowContent = content;
	threadOpts->WindowName = L"QuickWindow";

	qk_threads[index] = CreateThread(
		NULL,
		0,
		ThreadFuncHandleWindows,
		threadOpts,
		0,
		&qk_threadid[index]);

	return;
}

#elif
void QuickCreateWindow(TgaFile* content)
{
}
#endif // _WIN32


