#pragma once

#include "GameEngine.h"

#include <string>

class GameEngine;

class GameRule
{
public:
    GameRule(std::string identifier);
    ~GameRule();

    virtual void Update(GameEngine* engine);

    std::string RuleIdentifier;
};

