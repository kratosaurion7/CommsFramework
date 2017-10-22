#pragma once

class GraphicEngineInitParams;
class DrawObject;
class BaseSprite;
class BaseTexture;
class BaseFont;
class BaseText;
class Spritesheet;
class ImageLoader;

#include <Windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")
#undef CreateFont

#include <string>
#include <string.h>

#include "Collections/PointerList.h"
#include "Graphic/Base Classes/BaseGraphicEngine.h"

class DX2DGraphicEngine : public BaseGraphicEngine
{
public:
    ImageLoader* Loader;
    
    DX2DGraphicEngine();
    ~DX2DGraphicEngine();

    PointerList<DrawObject*>* drawables;

    virtual void Initialize(GraphicEngineInitParams* params);

    virtual void AddObject(BaseSprite* obj);
    virtual void AddObject(BaseText* obj);
    virtual void RemoveObject(DrawObject* obj);

    virtual void AddSpritesheet(Spritesheet* spritesheet);

    virtual PointerList<DrawObject*>* GetDrawableList();
    virtual DrawObject* GetDrawableObject(std::string identifier);

    virtual BaseSprite* CreateSpriteInstance();
    virtual BaseTexture* CreateTextureInstance();
    virtual BaseFont* CreateFontInstance();
    virtual BaseText* CreateTextInstance();

    virtual void ReloadSpriteTextures();

    virtual bool IsTimeForFrame();
    virtual int GetFramerate();
    virtual void SetFramerate(int framerate);
    virtual void SetAutoManagedFramerate(bool isSet);

    virtual void SetBackgroundColor(uint32_t color);
    virtual void SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    virtual void SetBackgroundTexture(BaseTexture* texture);

    virtual void Scale(float scaleFactor);

    virtual void Start();
    virtual void Draw();
    virtual void ProcessEvents();
    virtual void Stop();

    virtual bool IsRunning();

    virtual void ReorderSpritesByZIndex();
    virtual void FlagForZIndexSorting();
    virtual void ReorderSprite(DrawObject* first, DrawObject* second);

private:

    // Window
    HINSTANCE AppInstance;
    WNDCLASS MainWindowClass;
    HWND HMainWindow;

    //DirectX
    ID2D1Factory* D2Factory;
    ID2D1HwndRenderTarget* RenderTarget;

    IWICBitmapSource* TestBitmap;

    static LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

    // Init steps
    BOOL InitWindowApplication(std::string windowTitle, FSize* windowSize);

    BOOL InitDirect2D();

    DWORD ProcessWindowEvents();
};

