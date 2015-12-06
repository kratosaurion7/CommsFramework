#pragma once

#include <BaseActor.h>
#include <BaseList.h>
#include <PointerList.h>
#include <YesNoDialog.h>

#include "CardsShoe.h"
#include "BlackjackPlayer.h"
#include "BlackjackDealer.h"
#include "BetSelection.h"

#include "CardActor.h"

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
        DEALER_WINS,
        RESET,
        EXIT

    } GameState;

    BlackjackDealer* Dealer;
    BlackjackPlayer* Player;

    BetSelection* BetSelector;
    
    CardsShoe* GameCards;

    // Dialogs
    YesNoDialog* SplitCardsDialog;
    YesNoDialog* AskNewCardsDialog;

    BlackjackGame();
    ~BlackjackGame();

    void Update();

    void ResetGame();
};

