#pragma once

#include <BaseSprite.h>
#include <BaseActor.h>

class Card : public BaseActor
{
public:
    enum CARD_SUITS
    {
        SPADES,
        HEARTS,
        DIAMOND,
        CLUBS,

        CARD_SUITS_COUNT
    } CardSuit;

    enum CARD_VALUE
    {
        Ace = 1,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,

        CARD_VALUE_COUNT
    } CardValue;

    Card();
    ~Card();

    BaseSprite* cardFront;
    BaseSprite* cardBack;

    void TurnUp();

    void TurnDown(); // For what ??

    void Update();
};