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

    void Init();

    void Init(GameEngineInitParams* params);

    void Load();

    void Play();

    void Pre_Update();

    void Update();

    void Post_Update();

    BaseSprite* GetSprite(std::string name);

    BaseList<BaseSprite*>* GetSpriteList(std::string name);

    BaseSprite* CopySprite(std::string name, std::string newName);

private:
    GameEngineInitParams* engineInitParams;

    PointerList<BaseSprite*>* GameSprites;

    void CreateSpritesFromConfig();

    PointerList<BaseTexture*>* CreateTexturesFromResources(PointerList<Resource*>* resources);

    void BuildAnimationTextures(PointerList<SpriteAnimation*>* anims);
};

