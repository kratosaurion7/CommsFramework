#pragma once

#include "GraphicEngine.h"

#include "ResourceManager.h"

#include "BaseActor.h"
#include "BaseSprite.h"

#include "BaseKeyboard.h"
#include "BaseMouse.h"
#include "MouseClickInfo.h"

//#include "Network.h"
//#include "SocketClient.h"
//#include "SocketServer.h"

#include "GameRule.h"

#include "RandomGen.h"

#include "EngineDialogMessage.h"

#include <string>

#include "BaseQueue.h"

class GameRule;
class BaseActor;
class DrawObject;
class BaseSprite;
class EngineDialogMessage;

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

    static GameEngine* GetInstance();

    RandomGen* Rng;

    FSize* GameAreaSize;

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
    void DetachActor(BaseActor* actor);

    BaseSprite* CreateSprite(std::string spriteName);
    BaseSprite* CreateSprite(std::string spriteName, std::string spriteTexturePath);

    void RemoveSprite(BaseSprite* sprite);

    BaseSprite* GetSprite(std::string name);
    BaseList<BaseSprite*>* GetSpriteList(std::string name);

    BaseFont* GetGameDefaultFont();

    BaseText* CreateText(std::string text);
    BaseText* CreateText(std::string text, int textSize);
    BaseText* CreateText(std::string text, int textSize, uint32_t textColor);
    BaseText* CreateText(std::string text, int textSize, uint32_t textColor, BaseFont* typo);

    void RemoveText(BaseText* text);

    BaseSprite* CopySprite(std::string name, std::string newName);

    PointerList<BaseActor*>* GameActors;
    PointerList<BaseSprite*>* GameSprites;
    PointerList<BaseText*>* GameTexts;
    PointerList<GameRule*>* GameRules;

    void ShowEngineDialog(std::string engineMessageForDialog);
private:
    static GameEngine* _globalInstance; // Ugh, TODO CHANGE STATIC TO SOMETHING NOT BULLSHIT

    void FlagClickedSprites();
    void RemoveSpriteClickedFlag();
    MouseClickInfo* FrameClickInfo;

    GameEngineInitParams* engineInitParams;

    BaseFont* engineDefaultFont;

    void CreateSpritesFromConfig();

    void UpdateGraphicEngineSpritesFromActors();

    PointerList<BaseTexture*>* CreateTexturesFromResources(PointerList<Resource*>* resources);

    void BuildAnimationTextures(PointerList<SpriteAnimation*>* anims);
};

