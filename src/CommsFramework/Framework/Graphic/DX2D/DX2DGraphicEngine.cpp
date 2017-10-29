#ifdef WIN32
#include "DX2DGraphicEngine.h"

#include <wincodec.h>
#include <Windowsx.h>

#include "DX2DDrawable.h"
#include "DX2DSprite.h"
#include "DX2DTexture.h"
#include "DX2DText.h"
#include "DX2DFont.h"

#include "Geometry/FSize.h"
#include "System/Windows/ImageLoader.h"
#include "Graphic/DrawObject.h"
#include "Graphic/Viewport.h"
#include "System/Utilities.h"

DX2DGraphicEngine::DX2DGraphicEngine()
{
    TextureRepo = new TextureManager();
    Viewport = new ViewportRect();
    drawables = new PointerList<DrawObject*>();
    
    PreviousFrameTick = 0;
    CurrentFrameTick = 0;
    RenderingScaleX = 1;
    RenderingScaleY = 1;
    
    RunEngine = true;

    Loader = NULL;
    
    MouseX = 0;
    MouseY = 0;
    
    leftButtonState = BTN_RELEASED;
    rightButtonState = BTN_RELEASED;
    
}

DX2DGraphicEngine::~DX2DGraphicEngine()
{
    delete(Loader);
}

void DX2DGraphicEngine::Initialize(GraphicEngineInitParams* params)
{
    BOOL res = InitWindowApplication(params->WindowTitle, params->WindowSize);

    InitDirect2D();

    InitWIC();

    Loader = new DX2DTextureLoader(WicFactory, RenderTarget);
}

void DX2DGraphicEngine::AddObject(BaseSprite* obj)
{
    drawables->Add(obj);
    
    zIndexNeedsReordering = true;
}

void DX2DGraphicEngine::AddObject(BaseText* obj)
{
    drawables->Add(obj);
}

void DX2DGraphicEngine::RemoveObject(DrawObject* obj)
{
    drawables->RemoveObject(obj);
}

void DX2DGraphicEngine::AddSpritesheet(Spritesheet* spritesheet)
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

    hr = D2Factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            HMainWindow,
            D2D1::SizeU(
                rec.right - rec.left,
                rec.bottom - rec.top)
        ),
        &RenderTarget);

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

BOOL DX2DGraphicEngine::InitWIC()
{
    CoInitialize(NULL);

    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&WicFactory)
    );

    return SUCCEEDED(hr);
}

DWORD DX2DGraphicEngine::ProcessWindowEvents()
{
    MSG msg;
    BOOL bRet;
    while ((bRet = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) != 0)
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

void DX2DGraphicEngine::ProcessDraw()
{
    CurrentFrameTick = GetTicks();

    if (IsTimeForFrame() && RunEngine)
    {
        auto iter = this->drawables->GetContainer()->begin();
        while (iter != this->drawables->GetContainer()->end())
        {
            DrawObject* target = (*iter);

            if (target->IsVisible())
            {
                DX2DDrawable* drawImpl = dynamic_cast<DX2DDrawable*>(target);

                if (target->Ident != "")
                {
                    int i = 0;
                }

                if (drawImpl != NULL)
                {
                    D2D1_RECT_F dest;
                    dest.left = target->GetX();
                    dest.top = target->GetY();
                    dest.right = dest.left + target->GetWidth();
                    dest.bottom = dest.top + target->GetHeight();

                    ID2D1Bitmap* source = drawImpl->GetDrawableTexture();

                    if (source == NULL)
                    {
                        // TODO : Implement missing textures management.
                        break;
                    }

                    this->RenderTarget->DrawBitmap(source, dest);
                }
            }

            iter++;
        }

        PreviousFrameTick = CurrentFrameTick;
    }
}

PointerList<DrawObject*>* DX2DGraphicEngine::GetDrawableList()
{
    return drawables;
}

DrawObject* DX2DGraphicEngine::GetDrawableObject(std::string identifier)
{
    std::list<DrawObject*>::iterator iter = drawables->GetContainer()->begin();

    while (iter != drawables->GetContainer()->end())
    {
        DrawObject* targetSprite = (*iter);

        if (strcmp(targetSprite->Ident.c_str(), identifier.c_str()) == 0)
        {
            return targetSprite;
        }

        iter++;
    }

    return NULL;
}

BaseSprite* DX2DGraphicEngine::CreateSpriteInstance()
{
    DX2DSprite* spr = new DX2DSprite();
    spr->Engine = this;

    return spr;
}

BaseTexture* DX2DGraphicEngine::CreateTextureInstance()
{
    DX2DTexture* tex = new DX2DTexture();
    tex->Engine = this;
    tex->Graphics = this;

    return tex;
}

BaseFont* DX2DGraphicEngine::CreateFontInstance()
{
    DX2DFont* font = new DX2DFont();

    return font;
}

BaseText* DX2DGraphicEngine::CreateTextInstance()
{
    DX2DText* text = new DX2DText();

    return text;
}

void DX2DGraphicEngine::ReloadSpriteTextures()
{
}

void DX2DGraphicEngine::SetBackgroundColor(uint32_t color)
{
}

void DX2DGraphicEngine::SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
}

void DX2DGraphicEngine::SetBackgroundTexture(BaseTexture* texture)
{
}

void DX2DGraphicEngine::Scale(float scaleFactor)
{
}

void DX2DGraphicEngine::Start()
{
    RunEngine = true;
}

void DX2DGraphicEngine::Draw()
{
    PostMessage(HMainWindow, WM_PAINT, 0, 0);
}

void DX2DGraphicEngine::ProcessEvents()
{
    this->ProcessWindowEvents();
}

void DX2DGraphicEngine::Stop()
{
    RunEngine = false;
}

bool DX2DGraphicEngine::IsRunning()
{
    return RunEngine;
}

void DX2DGraphicEngine::ReorderSpritesByZIndex()
{
    auto spritesStart = this->drawables->GetContainer()->begin();
    auto spritesEnd = this->drawables->GetContainer()->end();

    drawables->GetContainer()->sort([](DrawObject* a, DrawObject* b) {
        return b->GetZIndex() > a->GetZIndex();
    });

    this->zIndexNeedsReordering = false;
}

void DX2DGraphicEngine::FlagForZIndexSorting()
{
    zIndexNeedsReordering = true;
}

void DX2DGraphicEngine::ReorderSprite(DrawObject * first, DrawObject * second)
{
    std::list<DrawObject*>* spriteslist = this->drawables->GetContainer();
    bool foundFirst = false;
    bool foundSecond = false;
    std::list<DrawObject*>::iterator iterFirst;
    std::list<DrawObject*>::iterator iterSecond;

    int loops = 0;

    auto it = spriteslist->begin();
    while (it != spriteslist->end())
    {
        DrawObject* iter = (*it);

        if (iter == first)
        {
            iterFirst = it;
            foundFirst = true;
        }
        else if (iter == second)
        {
            iterSecond = it;
            foundSecond = true;
        }

        if (foundFirst && foundSecond) // Early break
            break;

        it++;
        loops++;
    }

    if (foundFirst && foundSecond)
    {
        spriteslist->erase(iterSecond);

        spriteslist->insert(iterFirst, second);
    }

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

            engine->RenderTarget->BeginDraw();

            engine->ProcessDraw();

            engine->RenderTarget->EndDraw();
            
            EndPaint(hwnd, &ps);

            break;
        }
        case WM_LBUTTONDOWN:
        {
            engine->leftButtonState = BTN_CLICKED;

            printf("Click\n");
            
            break;
        }
        case WM_LBUTTONUP:
        {
            engine->leftButtonState = BTN_RELEASED;

            printf("Release\n");
            
            break;
        }
        case WM_MOUSEMOVE:
        {
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);

            engine->MouseX = xPos;
            engine->MouseY = yPos;
            
            //printf("x: %d, y: %d\n", xPos, yPos);

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