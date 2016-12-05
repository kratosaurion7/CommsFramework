#pragma once

class GameEngine;
class Spritesheet;
class FPosition;
class FRectangle;
class BaseSprite;
class BaseText;
class FSize;
class ConfigurationManager;
class XmlNode;

class World;
class Map;

class Player;
class PlayerCamera;

class CheatMenu;
class SimpleMenu;

#include <Vectors.h>
#include <string>
#include <PointerList.h>

class FantasyGame
{
public:
    FantasyGame();
    ~FantasyGame();

    void Init();

    GameEngine* Engine;

    World* GameWorld;
    Map* CurrentGrid;

    Player* GamePlayer;
    PlayerCamera* MainCamera;

    ConfigurationManager* Settings;

    // DEBUG STUFF
    CheatMenu* DebugCheatsMenu;
    PointerList<BaseText*>* TileIndexIdentifiers;

    void Start();

    void Play();

    virtual void Update();
    
    // TEST
    SimpleMenu* TestMenu;

private:

    // Fill up the settings repository with general settings
    void ReadCoreSettings();

    // Init Engine
    void InitEngine();

    // Init World

    void InitGraphics();
    void InitGame(); // Final init

    // CONFIG
    std::string assetsPath;

    BaseList<int>* createdWindows;

	// Config values
	float scaleFactor;
	float tileSize;
	float scaledSize;
};

FantasyGame* GetGameInstance();