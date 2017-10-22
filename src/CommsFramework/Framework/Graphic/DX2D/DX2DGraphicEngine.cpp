#include "DX2DGraphicEngine.h"

#ifdef WIN32

#include "Geometry\FSize.h"

DX2DGraphicEngine::DX2DGraphicEngine()
{
}

DX2DGraphicEngine::~DX2DGraphicEngine()
{
}

void DX2DGraphicEngine::Initialize(GraphicEngineInitParams * params)
{
    BOOL res = InitWindowApplication(params->WindowTitle, params->WindowSize);

    InitDirect2D();
}

void DX2DGraphicEngine::AddObject(BaseSprite * obj)
{
}

void DX2DGraphicEngine::AddObject(BaseText * obj)
{
}

void DX2DGraphicEngine::RemoveObject(DrawObject * obj)
{
}

void DX2DGraphicEngine::AddSpritesheet(Spritesheet * spritesheet)
{
}

BOOL DX2DGraphicEngine::InitWindowApplication(std::string windowTitle, FSize* windowSize)
{
    AppInstance = GetModuleHandle(NULL);

    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MainWindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = AppInstance;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
    wcex.lpszClassName = L"Game";

    if (!RegisterClassEx(&wcex))
    {
        DWORD err = GetLastError();
        printf("Error registring window class Game.\n");
        printf("Error = %d\n", err);

        return FALSE;
    }

    HMainWindow = CreateWindow(
        L"Game",
        L"GameWindow",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        (int)windowSize->Width, (int)windowSize->Height,
        NULL,
        NULL,
        AppInstance,
        0);

    if (HMainWindow == INVALID_HANDLE_VALUE)
    {
        DWORD err = GetLastError();
        printf("Unable to create the Main Window. Invalid Handle.\n");
        printf("Error = %d\n", err);

        return FALSE;
    }

    if (HMainWindow == NULL)
    {
        DWORD err = GetLastError();
        printf("Unable to create the Main Window. Return value was NULL.\n");
        printf("Error = %d\n", err);

        return FALSE;
    }

    SetWindowLongPtr(HMainWindow, GWLP_USERDATA, (UINT_PTR)this);

    return TRUE;
}

BOOL DX2DGraphicEngine::InitDirect2D()
{
    D2Factory = NULL;
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2Factory);

    if (hr != S_OK)
    {
        DWORD err = GetLastError();
        printf("Error creating the D2D factory. HR = %d\n", hr);
        printf("Error = %d\n", err);

        return FALSE;
    }

    RECT rec;
    GetClientRect(HMainWindow, &rec);
    
    ID2D1HwndRenderTarget* target;

    hr = D2Factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            HMainWindow,
            D2D1::SizeU(
                rec.right - rec.left,
                rec.bottom - rec.top)
        ),
        &target);

    if (hr != S_OK)
    {
        DWORD err = GetLastError();
        printf("Error creating the render target. HR = %d\n", hr);
        printf("Error = %d\n", err);
    }
    
    ShowWindow(HMainWindow, SW_SHOWNOACTIVATE);
    UpdateWindow(HMainWindow);

    return TRUE;
}

DWORD DX2DGraphicEngine::ProcessWindowEvents()
{
    MSG msg;
    BOOL bRet;
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            // handle the error and possibly exit
            DWORD err = GetLastError();
            printf("GetMessage returned -1.\n");
            printf("Error = %d\n", err);

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

PointerList<DrawObject*>* DX2DGraphicEngine::GetDrawableList()
{
    return nullptr;
}

DrawObject * DX2DGraphicEngine::GetDrawableObject(std::string identifier)
{
    return nullptr;
}

BaseSprite * DX2DGraphicEngine::CreateSpriteInstance()
{
    return nullptr;
}

BaseTexture * DX2DGraphicEngine::CreateTextureInstance()
{
    return nullptr;
}

BaseFont * DX2DGraphicEngine::CreateFontInstance()
{
    return nullptr;
}

BaseText * DX2DGraphicEngine::CreateTextInstance()
{
    return nullptr;
}

void DX2DGraphicEngine::ReloadSpriteTextures()
{
}

bool DX2DGraphicEngine::IsTimeForFrame()
{
    return false;
}

int DX2DGraphicEngine::GetFramerate()
{
    return 0;
}

void DX2DGraphicEngine::SetFramerate(int framerate)
{
}

void DX2DGraphicEngine::SetAutoManagedFramerate(bool isSet)
{
}

void DX2DGraphicEngine::SetBackgroundColor(uint32_t color)
{
}

void DX2DGraphicEngine::SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
}

void DX2DGraphicEngine::SetBackgroundTexture(BaseTexture * texture)
{
}

void DX2DGraphicEngine::Scale(float scaleFactor)
{
}

void DX2DGraphicEngine::Start()
{
}

void DX2DGraphicEngine::Draw()
{
}

void DX2DGraphicEngine::ProcessEvents()
{
    this->ProcessWindowEvents();
}

void DX2DGraphicEngine::Stop()
{
}

bool DX2DGraphicEngine::IsRunning()
{
    return false;
}

void DX2DGraphicEngine::ReorderSpritesByZIndex()
{
}

void DX2DGraphicEngine::FlagForZIndexSorting()
{
}

void DX2DGraphicEngine::ReorderSprite(DrawObject * first, DrawObject * second)
{
}

LRESULT CALLBACK DX2DGraphicEngine::MainWindowProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    DX2DGraphicEngine* engine = reinterpret_cast<DX2DGraphicEngine*>(
                                    static_cast<LONG_PTR>(
                                        GetWindowLongPtr(hwnd, GWLP_USERDATA)));

    switch (uiMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            engine->Draw();

            EndPaint(hwnd, &ps);

            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        default:
        {
            return DefWindowProc(hwnd, uiMsg, wParam, lParam);
        }
    }

    return 0;
}

#endif