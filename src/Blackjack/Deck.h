#pragma once

#include <BaseSprite.h>
#include <BaseActor.h>

#include <BaseList.h>
#include <PointerList.h>

#include "Card.h"

class Deck : public BaseActor
{
public:
    Deck();
    ~Deck();

    BaseList<Card*>* DeckCards;

    void ShuffleDeck();

    Card* DrawCard();
};