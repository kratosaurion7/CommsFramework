#pragma once

class BlackjackDealer;
class BlackjackPlayer;
class CardsShoe;
class YesNoDialog;
class MessageDialog;
class BetSelection;

#include <BaseList.h>
#include <PointerList.h>

#include <BaseActor.h>

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
        GAME_DRAW,
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

    MessageDialog* playerWinDialog;
    MessageDialog* playerLoseDialog;
    MessageDialog* gameDrawDialog;


    int gameDelay = 0;

    BlackjackGame();
    ~BlackjackGame();

    void Update();

    void ResetGame();
};

