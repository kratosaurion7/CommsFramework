#pragma once

#include "GraphicEngine.h"

#include "ResourceManager.h"

#include "GameObject.h"
#include "BaseSprite.h"

#include "BaseKeyboard.h"
#include "BaseMouse.h"

#include <string>

class GameObject;

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

    void AddGameObject(GameObject* obj);

    void Pre_Update();

    void Update();

    void Post_Update();

    BaseSprite* GetSprite(std::string name, bool copyOnly = true);

    BaseList<BaseSprite*>* GetSpriteList(std::string name);

private:
    GameEngineInitParams* engineInitParams;

    PointerList<GameObject*>* GameObjects;
    //PointerList<BaseSprite*>* GameSprites;

    void CreateSpritesFromConfig();

    PointerList<BaseTexture*>* CreateTexturesFromResources(PointerList<Resource*>* resources);

    void BuildAnimationTextures(PointerList<SpriteAnimation*>* anims);
};

