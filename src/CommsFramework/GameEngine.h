#pragma once

#include "GraphicEngine.h"

#include "ResourceManager.h"

#include "BaseActor.h"
#include "BaseSprite.h"

#include "BaseKeyboard.h"
#include "BaseMouse.h"

#include "GameRule.h"

#include <string>

class GameRule;
class BaseActor;

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

    void Init(int windowWidth, int windowHeight);

    void Init(GameEngineInitParams* params);

    void Load();

    void Play();

    void Pre_Update();

    void Update();

    void Draw();

    void Post_Update();

    BaseActor* CreateActor();
    BaseActor* CreateActor(BaseSprite* actorSprite);
    BaseActor* CreateActor(PointerList<DrawObject*>* spriteList);
    void AttachActor(BaseActor* actor);

    BaseSprite* CreateSprite(std::string spriteName);
    BaseSprite* CreateSprite(std::string spriteName, std::string spriteTexturePath);

    BaseFont* GetGameDefaultFont();

    BaseText* CreateText(std::string text);
    BaseText* CreateText(std::string text, BaseFont* typo);
    BaseText* CreateText(std::string text, BaseFont* typo, int textSize);

    BaseSprite* GetSprite(std::string name);
    BaseList<BaseSprite*>* GetSpriteList(std::string name);

    BaseSprite* CopySprite(std::string name, std::string newName);

    PointerList<BaseActor*>* GameActors;

    PointerList<BaseSprite*>* GameSprites;

    PointerList<BaseText*>* GameTexts;

    PointerList<GameRule*>* GameRules;
private:
    GameEngineInitParams* engineInitParams;

    BaseFont* engineDefaultFont;

    void CreateSpritesFromConfig();

    void UpdateGraphicEngineSpritesFromActors();

    PointerList<BaseTexture*>* CreateTexturesFromResources(PointerList<Resource*>* resources);

    void BuildAnimationTextures(PointerList<SpriteAnimation*>* anims);
};

