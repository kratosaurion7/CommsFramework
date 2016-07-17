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

    GameEngine* Engine;

    World* GameWorld;

    AreaGrid* CurrentArea;
    LocalGrid* CurrentGrid;

    Player* GamePlayer;
    PlayerCamera* MainCamera;

    void Start();

    void Play();

    virtual void Update();

	void Configure();

private:
    SettingsRepository* Settings;

    World* ReadWorldData(XmlNode* worldsNode);
};
