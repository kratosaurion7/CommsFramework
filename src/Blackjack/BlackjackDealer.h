#pragma once

#include <BaseList.h>
#include <PointerList.h>
#include <BaseActor.h>

#include "Card.h"


class BlackjackDealer : public BaseActor
{
public:
    BlackjackDealer();
    ~BlackjackDealer();

    PointerList<Card*>* DealerCards;

    int CardsTotal();

    bool BlackjackIsPossible();
};

