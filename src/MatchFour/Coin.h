#pragma once

#include <BaseSprite.h>

enum CoinStates
{
    COIN_IDLE,
    COIN_START_SPIN,
    COIN_SPIN,
    COIN_END_SPIN,

    COIN_STATES_COUNT
};

class Coin
{
public:
    Coin();
    ~Coin();

    CoinStates CurrentState;

    BaseSprite* CoinSprite;

    void Update(); // Pass state parameter ?
private:
    int coinSpinCounter = 0;

    int idleCounter = 0;

    std::string animationToStart;
};

