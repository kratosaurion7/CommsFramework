#pragma once

#include "GraphicEngine.h"

#include "ResourceManager.h"

#include "BaseSprite.h"

#include "BaseKeyboard.h"
#include "BaseMouse.h"

#include <string>

struct GameEngineInitParams
{
    GraphicEngineInitParams* GraphicsParams;

    ResourceManagerInitParams* ResourceParams;

    static GameEngineInitParams* CreateDefaultParams();
};

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    GraphicEngine* Graphics;
    ResourceManager* Resources;

    static BaseKeyboard* Keyboard;
    static BaseMouse* Mouse;

    void Init(GameEngineInitParams* params);

    void Load();

    void Pre_Update();

    void Update();

    void Post_Update();

    BaseSprite* GetSprite(std::string name);
private:
    GameEngineInitParams* engineInitParams;

    void CreateSpritesFromConfig();

    PointerList<BaseTexture*>* CreateTexturesFromResources(PointerList<Resource*>* resources);
};

