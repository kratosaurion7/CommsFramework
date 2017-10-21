#pragma once

class Card;
class Deck;
class GameEngine;

#include <Collections/BaseList.h>
#include <Collections/PointerList.h>

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

    PointerList<Card*>* DrawnCards;
};

