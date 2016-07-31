#include "Utils.h"

#include "TgaFile.h"

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
    wc.lpfnWndProc = WndProc;
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
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
            break;
        }
    }

    return DefWindowProc(hwnd, uiMsg, wParam, lParam);
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
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void DoPaint(HWND window)
{

}

int GetNextFreeHwndIndex()
{
    for (int i = 0; i < MAX_QUICKWINDOWS; i++)
    {
        if (qk_hwnd[i] == NULL)
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
        return;

    HWND hwnd = CreateWindow(
        L"CommsFramework",
        L"QuickWindow",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        content->Width, content->Height,
        NULL,
        NULL,
        qk_inst,
        0);

    qk_hwnd[index] = hwnd;

    ShowWindow(hwnd, GetNCmdShow());
    UpdateWindow(hwnd);

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
        &RenderTarget[index]);

    ID2D1Bitmap* bmp;
    D2D1_SIZE_U size;
    size.height = content->Height;
    size.width = content->Width;
    D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties();
    props.pixelFormat = D2D1_PIXEL_FORMAT();
    props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
    props.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;

    hr = RenderTarget[index]->CreateBitmap(size, props, &bmp);
    hr = bmp->CopyFromMemory(0, content->Pixels, 32);

    ID2D1BitmapBrush* bru;
    hr = RenderTarget[index]->CreateBitmapBrush(bmp, &bru);
    BGBrush[index] = bru;

    if (FAILED(hr))
    {
        std::string x = GetLastErrorString();

        return;
    }

    qk_threads[index] = CreateThread(
        NULL,
        0,
        ThreadFuncHandleWindows,
        NULL,
        0,
        &qk_threadid[index]);
}

#elif
void QuickCreateWindow(TgaFile* content)
{
}
#endif // _WIN32


