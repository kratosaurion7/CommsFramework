#pragma once

class CardHand;

#include <Collections/BaseList.h>
#include <Collections/PointerList.h>

#include "CardActor.h"

class BlackjackDealer : public CardActor
{
public:
    BlackjackDealer();
    ~BlackjackDealer();

    bool BlackjackIsPossible(int handIndex = 0);
    bool BlackjackIsPossible(CardHand* targetHand);

    bool NeedsMoreCards();

    void Update();

protected:
    virtual void UpdateCardPositions(int handIndex = 0);
    virtual void UpdateCardPosition(CardHand* targetHand);


};

