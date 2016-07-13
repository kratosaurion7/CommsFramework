#pragma once

class GameEngine;
class Spritesheet;
class FPosition;
class FSize;

class World;
class AreaGrid;
class LocalGrid;

class Player;
class PlayerCamera;

#include <string>
#include <PointerList.h>

struct Game_Start_Params
{
	std::string GameName;

    PointerList<Spritesheet*>* Spritesheets;

    FPosition* CameraStart;
    FSize* CameraSize;
};

class FantasyGame
{
public:
    FantasyGame();
    ~FantasyGame();

    GameEngine* Engine;

    World* GameWorld;

    AreaGrid* CurrentArea;
    LocalGrid* CurrentGrid;

    Player* GamePlayer;
    PlayerCamera* MainCamera;

    void Start(Game_Start_Params* startingParams);

    void Play();

    virtual void Update();

	Game_Start_Params* ReadParametersConfig(std::string configFilePath);
};
