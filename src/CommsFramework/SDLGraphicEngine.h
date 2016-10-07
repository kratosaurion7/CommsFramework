#pragma once

class DrawObject;
class GraphicEngineInitParams;
class BaseSprite;
class BaseText;
class BaseTexture;
class BaseFont;
class BaseText;
class Spritesheet;

struct SDL_Rect;
struct SDL_Window;
struct SDL_Renderer;

#include <string>
#include <cstdint>

#include "PointerList.h"

#include "BaseGraphicEngine.h"

class SDLGraphicEngine : public BaseGraphicEngine
{
public:
    GraphicEngineInitParams* startParams;

    SDL_Window* mainWindow;
    SDL_Renderer* gameRenderer;

    uint8_t bg_r;
    uint8_t bg_g;
    uint8_t bg_b;
    uint8_t bg_a;

    /* After calling the Initialize() method, this value will tell if the engine is ready or not. */
    bool engineValid = false;

    PointerList<DrawObject*>* drawables;

    PointerList<Spritesheet*>* Spritesheets;

    SDLGraphicEngine();
    ~SDLGraphicEngine();

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
    int WantedFrameRate;
    bool RunEngine;

    BaseSprite* backgroundSprite;

    void ProcessDraw(SDL_Window* targetWindow);
    void ProcessEvents(SDL_Window* targetWindow);

    SDL_Rect GetSpriteRect(DrawObject* object);

    

    void SetupBackground();
    
#ifdef WIN32
    void InitWin32();

    void SetupDPI();
#endif

};

