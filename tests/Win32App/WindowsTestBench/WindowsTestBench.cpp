// WindowsTestBench.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WindowsTestBench.h"

#include <d2d1.h>
#include <wincodec.h>
#include <wincodecsdk.h>


#include <ImageLoader.h>
#include <TgaFile.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND MainWindow;

// D2
ID2D1Factory* D2Factory = NULL;
ID2D1HwndRenderTarget* RenderTarget = NULL;
ID2D1SolidColorBrush* DefaultBrush = NULL;
ID2D1BitmapBrush* BGBrush;
IWICBitmap* bgImage;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
BOOL                InitDevice(HWND window);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL				ReCreateRenderTarget(HWND window);

void DoPaint(HWND);

#define IDC_MAIN_BUTTON 101
HWND myButton;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    //ImageLoader* loader = new ImageLoader();

    //TgaFile* tga = new TgaFile();
    //tga->Init(300, 300);
    //tga->FillColor(0, 255, 0, 255);

    //bgImage = loader->CreateBitmap(tga, false);

    
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSTESTBENCH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    if (!InitDevice(MainWindow))
    {
        return FALSE;
    }

    ShowWindow(MainWindow, nCmdShow);
    UpdateWindow(MainWindow);


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSTESTBENCH));

	if (myButton == NULL)
	{
		std::string err = GetLastErrorString();

		int i = 0;
	}

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSTESTBENCH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSTESTBENCH);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   MainWindow = hWnd;


   return TRUE;
}

BOOL InitDevice(HWND window)
{
    HRESULT hr = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &D2Factory
    );

    if (FAILED(hr))
    {
        std::string err = GetLastErrorString();

		fprintf(stderr, "%s", err);

        return FALSE;
    }

	ReCreateRenderTarget(window);
    
    if (FAILED(hr))
    {
        std::string err = GetLastErrorString();

        return FALSE;
    }

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		case WM_CREATE:
		{
			myButton = CreateWindowEx(NULL,
				L"BUTTON",
				L"OK",
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				20, 20,
				100, 100,
				hWnd,
				(HMENU)IDC_MAIN_BUTTON,
				GetModuleHandle(NULL),
				NULL);

			break;
		}
        case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);
				int hi = HIWORD(wParam);
				
                // Parse the menu selections:
                switch (wmId)
                {
					case IDM_ABOUT:
						DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
						break;
					case IDM_EXIT:
						DestroyWindow(hWnd);
						break;
					case IDC_MAIN_BUTTON:
						Beep(400, 50);
						break;
					default:
						return DefWindowProc(hWnd, message, wParam, lParam);
                }
                
                break;
            }
        case WM_PAINT:
            {
                PAINTSTRUCT ps;

                //DoPaint(MainWindow);

                EndPaint(hWnd, &ps);
                
                break;
            }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
		case WM_SIZE:
		{
			ReCreateRenderTarget(hWnd);
			break;
		}
        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
        {
            return (INT_PTR)TRUE;
        }
        case WM_COMMAND:
        {
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }
    }

    return (INT_PTR)FALSE;
}

BOOL ReCreateRenderTarget(HWND window)
{
	if (RenderTarget != NULL)
	{
		RenderTarget->Release();
		RenderTarget = NULL;
	}

	if (DefaultBrush != NULL)
	{
		DefaultBrush->Release();;
		DefaultBrush = NULL;
	}

	RECT rec;
	GetClientRect(window, &rec);

    D2D1_RENDER_TARGET_PROPERTIES format = D2D1::RenderTargetProperties();
    format.pixelFormat = D2D1_PIXEL_FORMAT();
    format.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
    format.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;

	HRESULT hr = D2Factory->CreateHwndRenderTarget(
        format,
		D2D1::HwndRenderTargetProperties(
			window,
			D2D1::SizeU(
				rec.right - rec.left,
				rec.bottom - rec.top)
		),
		&RenderTarget);

	if (FAILED(hr))
	{
		std::string err = GetLastErrorString();

		return FALSE;
	}
}

void DoPaint(HWND target)
{
    if (BGBrush == NULL)
    {
        //HRESULT hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &DefaultBrush);
        ID2D1Bitmap* outbit;
        HRESULT hr = RenderTarget->CreateBitmapFromWicBitmap(bgImage, &outbit);
        hr = RenderTarget->CreateBitmapBrush(outbit, &BGBrush);

        //ID2D1Bitmap* bgBitmap = NULL;
        //
        //hr = RenderTarget->CreateBitmapFromWicBitmap(bgImage, &bgBitmap);

        //RenderTarget->CreateBitmapBrush(bgBitmap, &BGBrush);

        if (FAILED(hr))
        {
            std::string err = GetLastErrorString();

            return;
        }
    }

    RECT rc;
    GetClientRect(target, &rc);

    RenderTarget->BeginDraw();

	RenderTarget->Clear();
    RenderTarget->FillRectangle(
        D2D1::RectF(
			rc.left + 100.0f,
			rc.top + 100.0f,
			rc.right - 100.0f,
			rc.bottom - 100.0f),
        BGBrush);

    

    HRESULT hr = RenderTarget->EndDraw();

}
