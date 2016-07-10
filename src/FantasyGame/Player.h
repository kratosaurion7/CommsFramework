#pragma once

#include <string>
#include <BaseActor.h>

class Player : public BaseActor
{
public:
    Player();
    ~Player();

    std::string PlayerName;

    virtual void Update();
};

