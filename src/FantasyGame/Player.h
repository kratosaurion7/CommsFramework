#pragma once

class BaseSprite;

#include <string>
#include <Game/Actors/BaseActor.h>
#include <Geometry/Vectors.h>

class Player : public BaseActor
{
public:
    std::string PlayerName;

    BaseSprite* PlayerSprite;

    // Movement
    FloatVec Speed;

    Player();
    ~Player();


    virtual void Update();
};

