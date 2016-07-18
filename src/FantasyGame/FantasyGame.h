#pragma once

class GameEngine;
class Spritesheet;
class FPosition;
class FSize;
class SettingsRepository;
class XmlNode;

class World;
class AreaGrid;
class LocalGrid;

class Player;
class PlayerCamera;

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
};
