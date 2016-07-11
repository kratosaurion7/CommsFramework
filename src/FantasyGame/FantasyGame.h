#pragma once

class GameEngine;

class World;
class AreaGrid;
class LocalGrid;

class Player;
class PlayerCamera;


#include <PointerList.h>

struct Game_Start_Params
{

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
};
