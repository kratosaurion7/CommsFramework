#include "Card.h"



Card::Card()
{
    this->cardBack = NULL;
    this->cardFront = NULL;

    this->CardSuit = (Card::CARD_SUITS)0;
    this->CardValue = (Card::CARD_VALUE)0;
}


Card::~Card()
{
    if (this->cardBack != NULL)
    {
        this->Engine->Graphics->RemoveObject(cardBack);

        delete(cardBack);
    }

    if (this->cardFront != NULL)
    {
        this->Engine->Graphics->RemoveObject(cardFront);

        delete(cardFront);
    }

    Engine->DetachActor(this);
}

void Card::Update()
{
}
