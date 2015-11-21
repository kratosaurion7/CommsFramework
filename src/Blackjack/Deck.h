#pragma once

#include <GameEngine.h>

#include <BaseSprite.h>
#include <BaseActor.h>

#include <BaseList.h>
#include <PointerList.h>
#include <BaseStack.h>

#include "Card.h"

class Deck : public BaseActor
{
public:
    Deck(GameEngine* engine);
    ~Deck();

    BaseStack<Card*>* DeckCards;

    void SetupStandard52CardsDeck();

    void ShuffleDeck();

    Card* DrawCard();
private:
    GameEngine* Engine;

    void SetupCardSprites(Card* targetCard);

    void AssignCardSprites();

    void PositionCards();
};