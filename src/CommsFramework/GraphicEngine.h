#pragma once

#include <SFML\Graphics.hpp>

#include "PointerList.h"

#include "SFMLDrawable.h"

#include "DrawObject.h"
#include "DSprite.h"
#include "SFMLText.h"

#include "GraphicEngineInitParams.h"

#include "BaseGraphicEngine.h"

class GraphicEngine : public BaseGraphicEngine
{
public:
    GraphicEngine();
    ~GraphicEngine();

    PointerList<DrawObject*>* Sprites;
    sf::RenderWindow* MainWindow;

    void Initialize(GraphicEngineInitParams* params);

    void AddObject(BaseSprite* obj);

    void AddObject(BaseText* obj);

    void RemoveObject(DrawObject* obj);

    DrawObject* GetObject(std::string identifier);

    BaseSprite* CreateSprite(std::string identifier = "");
    BaseTexture* CreateTexture();
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

private:
    bool isRunning;

    bool zIndexNeedsReordering = false;

    int _sfmlFramerate;

    sf::Color backgroundColor;

    GraphicEngineInitParams* startParams;

    void ProcessWindowsEvents(sf::RenderWindow* targetWindow);

    void ProcessDraw(sf::RenderWindow* targetWindow);
};

