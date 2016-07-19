#pragma once

class GameEngine;
class Spritesheet;
class FPosition;
class FRectangle;
class FSize;
class SettingsRepository;
class XmlNode;

class World;
class AreaGrid;
class LocalGrid;

class Player;
class PlayerCamera;

#include <Vectors.h>
#include <string>
#include <PointerList.h>

class FantasyGame
{
public:
    FantasyGame();
    ~FantasyGame();

    void Init();

	void ReadConfig();

    GameEngine* Engine;

    World* GameWorld;

    AreaGrid* CurrentArea;
    LocalGrid* CurrentGrid;

    Player* GamePlayer;
    PlayerCamera* MainCamera;

    SettingsRepository* Settings;

    void Start();

    void Play();

    virtual void Update();
    
private:

    World* ReadWorldData(std::string worldXmlConfigFile);

    // CONFIG
    float _tile_size;
    float _cameraX;
    float _cameraY;
    float _cameraHeights;
    float _cameraWidth;

    FRectangle* camFov;
    Vector2<int>* camSpeed;
};
