#pragma once

class RandomGen;
struct GameEngineInitParams;
class GraphicEngineInitParams;
class GameRule;

class ConfigurationManager;

class BaseGraphicEngine;

class BaseSprite;
class BaseSprite;
class BaseText;
class BaseActor;
class BaseFont;
class BaseTexture;

class BaseKeyboard;
class BaseMouse;

class Resource;
class DrawObject;
class EngineDialogMessage;

struct MouseClickInfo;
class FSize;


#include "Collections/PointerList.h"
#include <string>
#include <stdint.h>
#include <limits.h>

struct PRIO
{
    enum OBJECTS_PRIO
    {
        OVERRIDE_BACK = 0,
        BACKGROUND = 1,
        SCENE_BACK = 50,
        SCENE_FRONT = 100,
        MESSAGE = 140,
        UI = 150,
        DIALOG = 160,
        DEBUG = 999,
        OVERRIDE_TOPMOST = UINT_MAX // This needs to stay THE TOPMOST ELEMENT
    };

};

struct GameEngineInitParams
{
    GraphicEngineInitParams* GraphicsParams;


    static GameEngineInitParams* CreateDefaultParams();
};

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    ConfigurationManager* ConfigManager;

    BaseGraphicEngine* Graphics;

    static BaseKeyboard* Keyboard;
    static BaseMouse* Mouse;

    MouseClickInfo* FrameClickInfo;

    static GameEngine* GetInstance();

    RandomGen* Rng;

    FSize* GameAreaSize;

    void Init();

    void Init(float windowWidth, float windowHeight);

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

    BaseSprite* CreateSprite();
    BaseSprite* CreateSprite(std::string spriteName);
    BaseSprite* CreateSprite(std::string spriteName, std::string spriteTexturePath);

    void RemoveSprite(BaseSprite* sprite);

    BaseSprite* GetSprite(std::string name);
    BaseList<BaseSprite*>* GetSpriteList(std::string name);

	BaseTexture* CreateTexture();

	BaseFont* CreateFont();

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

    void PlayLoop();
    void StopLoop();

private:
    static GameEngine* _globalInstance; // Ugh, TODO CHANGE STATIC TO SOMETHING NOT BULLSHIT

    bool LoopEngine;

    void FlagClickedSprites();
    void RemoveSpriteClickedFlag();

    void DoEventLoop();

    GameEngineInitParams* engineInitParams;

    BaseFont* engineDefaultFont;

    void CreateSpritesFromConfig();

    void UpdateGraphicEngineSpritesFromActors();
};

