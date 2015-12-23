#pragma once

class BaseText;

#include <BaseList.h>
#include <PointerList.h>

#include "CardActor.h"

class BlackjackPlayer : public CardActor
{
public:
    BaseText* MoneyText;
    BaseText* MoneyLabel;

    BaseText* LastBetLabel;
    BaseText* LastBetText;

    BaseText* CurrentBetLabel;
    BaseText* CurrentBetText;

    int Money;

    int LastBet;
    int CurrentBet;

    BlackjackPlayer();
    ~BlackjackPlayer();

    bool CanSplit();

protected:
    virtual void UpdateCardPositions();

    virtual void UpdateStatusTexts();
};