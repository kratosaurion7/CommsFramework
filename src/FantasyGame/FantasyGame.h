#pragma once

#include <BaseActor.h>

class World;
class AreaGrid;
class LocalGrid;

class Player;
class PlayerCamera;

#include <PointerList.h>

struct Game_Start_Params
{

};

class FantasyGame : public BaseActor
{
public:
    FantasyGame();
    ~FantasyGame();

    World* GameWorld;

    AreaGrid* CurrentArea;
    LocalGrid* CurrentGrid;

    Player* GamePlayer;
    PlayerCamera* MainCamera;

    void Start(Game_Start_Params* startingParams);

    virtual void Update();
};
