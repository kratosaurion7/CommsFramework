#include "Utils.h"

#include "TgaFile.h"

HANDLE outMut;

HINSTANCE qk_inst;
HWND qk_hwnd[MAX_QUICKWINDOWS] = { 0 };
HANDLE qk_threads[MAX_QUICKWINDOWS] = { 0 };
DWORD qk_threadid[MAX_QUICKWINDOWS] = { 0 };


void stprintf(char* buf)
{
};

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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg) 
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

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
    ::STARTUPINFOW startupInfo;
    ::GetStartupInfoW(&startupInfo);
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

int GetNextFreeHwndIndex()
{
    for (int i = 0; i < MAX_QUICKWINDOWS; i++)
    {
        if (qk_hwnd[i] == NULL)
            return i;
    }

    return -1;
}

void QuickCreateWindow(TgaFile * content)
{
#ifdef _WIN32
    if (qk_inst == NULL)
    {
        qk_inst = GetModuleHandle(nullptr);

        if (!InitApp()) return;
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

    if (hwnd == NULL)
    {
        std::string err = GetLastErrorString();

        fprintf(stderr, "%s", err);

        return;
    }

    qk_hwnd[index] = hwnd;

    ShowWindow(hwnd, GetNCmdShow());
    UpdateWindow(hwnd);

    qk_threads[index] = CreateThread(
        NULL,
        0,
        ThreadFuncHandleWindows,
        NULL,
        0,
        &qk_threadid[index]);


    //MSG msg;
    //while (GetMessage(&msg, NULL, 0, 0)) {
    //    TranslateMessage(&msg);
    //    DispatchMessage(&msg);
    //}


#endif
}
