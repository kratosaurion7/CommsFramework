#pragma once

class BaseGraphicEngine;
class DrawObject;
class GraphicEngineInitParams;
class SFMLText;
class DSprite;
class BaseSprite;
class BaseText;
class BaseTexture;
class BaseFont;

#include <cstdint>

#include <SFML\Graphics.hpp>

#include "PointerList.h"
#include "BaseGraphicEngine.h"

class SFMLGraphicEngine : public BaseGraphicEngine
{
public:
    SFMLGraphicEngine();
    ~SFMLGraphicEngine();

    PointerList<DrawObject*>* Sprites;
    sf::RenderWindow* MainWindow;

    void Initialize(GraphicEngineInitParams* params);

    void AddObject(BaseSprite* obj);
    void AddObject(BaseText* obj);
    void RemoveObject(DrawObject* obj);

    PointerList<DrawObject*>* GetDrawableList();
    DrawObject* GetDrawableObject(std::string identifier);

    BaseSprite* CreateSprite(std::string identifier = "");
    BaseTexture* CreateTexture();
    BaseTexture* CreateTexture(std::string texturePath);
    BaseFont* CreateFont();
    BaseText* CreateText();

    int GetFramerate();

    void SetFramerate(int framerate);

    void SetAutoManagedFramerate(bool isSet = true);

    void SetBackgroundColor(uint32_t color);

    void SetBackgroundTexture(BaseTexture* texture);

    void Start();

    void Draw();

    void ProcessEvents();

    void Stop();

    bool IsRunning();

    void ReorderSpritesByZIndex();

    void FlagForZIndexSorting();

    void ReorderSprite(DrawObject* first, DrawObject* second);

private:
    bool isRunning;
    
    int _sfmlFramerate;

    sf::Color backgroundColor;

    GraphicEngineInitParams* startParams;

    void ProcessWindowsEvents(sf::RenderWindow* targetWindow);

    void ProcessDraw(sf::RenderWindow* targetWindow);
};

