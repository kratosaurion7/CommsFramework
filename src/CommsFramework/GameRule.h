#pragma once

#include "GameEngine.h"

class GameRule
{
public:
    GameRule();
    ~GameRule();

    virtual void Update(GameEngine* engine);
};

