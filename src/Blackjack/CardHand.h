#pragma once

class Card;

#include <Collections/PointerList.h>

class CardHand
{
public:
    CardHand();
    ~CardHand();

    PointerList<Card*>* Cards;

    int GetTotal();
};

