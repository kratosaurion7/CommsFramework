#pragma once

#include <BaseSprite.h>
#include <BaseActor.h>

#include <BaseList.h>
#include <PointerList.h>
#include <BaseStack.h>

#include "Card.h"

class Deck : public BaseActor
{
public:
    Deck();
    ~Deck();

    BaseStack<Card*>* DeckCards;

    void SetupStandard52CardsDeck();

    void ShuffleDeck();

    Card* DrawCard();
};