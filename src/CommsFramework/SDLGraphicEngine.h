#pragma once

class DrawObject;
class GraphicEngineInitParams;
class BaseSprite;
class BaseText;
class BaseTexture;
class BaseFont;
class BaseText;

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

    /* After calling the Initialize() method, this value will tell if the engine is ready or not. */
    bool engineValid = false;

    PointerList<DrawObject*>* drawables;

    SDLGraphicEngine();
    ~SDLGraphicEngine();

    virtual void Initialize(GraphicEngineInitParams* params);

    virtual void AddObject(BaseSprite* obj);
    virtual void AddObject(BaseText* obj);
    virtual void RemoveObject(DrawObject* obj);

    virtual PointerList<DrawObject*>* GetDrawableList();
    virtual DrawObject* GetObject(std::string identifier);

    virtual BaseSprite* CreateSprite(std::string identifier = "");
    virtual BaseTexture* CreateTexture();
    virtual BaseTexture* CreateTexture(std::string texturePath);
    virtual BaseFont* CreateFont();
    virtual BaseText* CreateText();

    virtual int GetFramerate();
    virtual void SetFramerate(int framerate);
    virtual void SetAutoManagedFramerate(bool isSet);

    virtual  void SetBackgroundColor(uint32_t color);
    virtual void SetBackgroundTexture(BaseTexture* texture);

    virtual void Start();
    virtual void Draw();
    virtual void ProcessEvents();
    virtual void Stop();

    virtual bool IsRunning();

    virtual void ReorderSpritesByZIndex();
    virtual void FlagForZIndexSorting();
    virtual void ReorderSprite(DrawObject* first, DrawObject* second);
};

