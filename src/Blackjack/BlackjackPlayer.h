#pragma once

class BaseText;
class CardHand;

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
    int OriginalBet;
    int CurrentBet;

    bool DoubledBet;

    BlackjackPlayer();
    ~BlackjackPlayer();

    bool CanSplit(int handIndex = 0);
    bool CanSplit(CardHand* targetHand);

protected:
    virtual void UpdateCardPositions(int handIndex = 0);
    virtual void UpdateCardPosition(CardHand* targetHand);

    virtual void UpdateStatusTexts();
};