#pragma once

#include <BaseActor.h>
#include <BaseList.h>
#include <PointerList.h>

#include "CardsShoe.h"

class BlackjackGame : public BaseActor
{
public:
    enum Game_State
    {
        START,
        CHOOSE_BET,
        RECEIVE_CARDS,
        ASK_SPLIT,
        ASK_INSURANCE,
        PLAYER_NEW_CARDS,
        DEALER_NEW_CARDS,
        GAME_FINISHED,
        PLAYER_WINS,
        DEALER_WINS

    };

    CardsShoe* GameCards;

    BlackjackGame();
    ~BlackjackGame();

    void Process_State();
};

