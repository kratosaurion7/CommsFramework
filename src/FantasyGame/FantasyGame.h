#pragma once

#include <BaseActor.h>

class World;
class AreaGrid;
class LocalGrid;

class Player;
class PlayerCamera;

#include <PointerList.h>

class FantasyGame : public BaseActor
{
public:
    FantasyGame();
    ~FantasyGame();

    World* GameWorld;

    Player* GamePlayer;
    PlayerCamera* MainCamera;

    virtual void Update();

private:
    void SetupPlayer(Player* target);
};
