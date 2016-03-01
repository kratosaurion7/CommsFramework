#pragma once

class Card;

#include <PointerList.h>

class CardHand
{
public:
    CardHand();
    ~CardHand();

    PointerList<Card*>* Cards;

    int GetTotal();
};

