#pragma once

#include <BaseList.h>
#include <PointerList.h>
#include <BaseActor.h>
#include <GameEngine.h>

#include "Card.h"

#include "CardActor.h"

class BlackjackPlayer : public CardActor
{
public:
    int Money;

    int LastBet;
    int CurrentBet;

    BlackjackPlayer();
    ~BlackjackPlayer();

    bool CanSplit();

protected:
    virtual void UpdateCardPositions();
};