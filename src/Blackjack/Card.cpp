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
        delete(cardBack);

    if (this->cardFront != NULL)
        delete(cardFront);
}

void Card::Update()
{
}
