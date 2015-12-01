#pragma once

#include <BaseList.h>
#include <PointerList.h>
#include <BaseActor.h>

#include "Card.h"

class BlackjackPlayer
{
public:
    enum CardChoosing
    {
        IDLE,
        ASKING_NEW_CARD,
        ACCEPTED_CARD,
        NO_NEW_CARD
    } CardChoosingState;

    enum PlayerStatus
    {
        OK,
        BUSTED
    } PlayerStatus;

    int Money;

    int LastBet;
    int CurrentBet;

    PointerList<Card*>* PlayerCards;

    BlackjackPlayer();
    ~BlackjackPlayer();

    int CardsTotal();

    bool CanSplit();

    void ReceiveCard(Card* card);
};