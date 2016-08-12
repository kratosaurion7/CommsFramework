#pragma once

class BaseSprite;

#include <string>
#include <BaseActor.h>

class Player : public BaseActor
{
public:
    std::string PlayerName;

    BaseSprite* PlayerSprite;

    Player();
    ~Player();


    virtual void Update();
};

