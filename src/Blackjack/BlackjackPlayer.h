#pragma once

#include <BaseList.h>
#include <PointerList.h>
#include <BaseActor.h>

#include "Card.h"

class BlackjackPlayer
{
public:
    BlackjackPlayer();
    ~BlackjackPlayer();

    int Money;

    int LastBet;
    int CurrentBet;

    PointerList<Card*>* PlayerCards;

    int CardsTotal();

    bool CanSplit();
};

