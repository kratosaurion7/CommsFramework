#pragma once

#include "GraphicEngine.h"

#include "ResourceManager.h"

#include "BaseSprite.h"

#include "BaseKeyboard.h"
#include "BaseMouse.h"

#include "GameRule.h"

#include <string>

class GameRule;

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
    
    BaseSprite* CreateSprite(std::string spriteName);

    BaseSprite* CreateSprite(std::string spriteName, std::string spriteTexturePath);

    BaseSprite* GetSprite(std::string name);

    BaseList<BaseSprite*>* GetSpriteList(std::string name);

    BaseSprite* CopySprite(std::string name, std::string newName);

    PointerList<BaseSprite*>* GameSprites;

    PointerList<GameRule*>* GameRules;
private:
    GameEngineInitParams* engineInitParams;

    void CreateSpritesFromConfig();

    PointerList<BaseTexture*>* CreateTexturesFromResources(PointerList<Resource*>* resources);

    void BuildAnimationTextures(PointerList<SpriteAnimation*>* anims);
};

