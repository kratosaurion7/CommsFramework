#pragma once

#include <BaseActor.h>
#include <PointerList.h>

class Card;
class Deck;
class GameEngine;

class CardsShoe
{
public:
    CardsShoe();
    ~CardsShoe();

    Card* DrawCard();

    int CardsLeft();

    void ReSeedDeck(int amountOfDecks = 3);

private:
    GameEngine* Engine;

    PointerList<Deck*>* Decks;

    PointerList<Card*>* DiscartPile;
};

