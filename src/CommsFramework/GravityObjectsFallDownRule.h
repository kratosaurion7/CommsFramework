#pragma once

#include "GameRule.h"

class GravityObjectsFallDownRule : public GameRule
{
public:
    GravityObjectsFallDownRule();
    ~GravityObjectsFallDownRule();

    virtual void Update(GameEngine* engine);
};

