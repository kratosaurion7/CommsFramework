#pragma once

class GameEngine;
class Card;

#include <PointerList.h>
#include <BaseStack.h>
#include <BaseActor.h>


class Deck : public BaseActor
{
public:
    Deck(GameEngine* engine);
    ~Deck();

    BaseStack<Card*>* DeckCards;

    void SetupStandard52CardsDeck();

    void SetupTestAcesDeck();

    void ShuffleDeck();

    Card* DrawCard();

    void SpreadCardsOnScreen();
private:
    GameEngine* Engine;

    void SetupCardSprites(Card* targetCard);

    void AssignCardSprites();
};