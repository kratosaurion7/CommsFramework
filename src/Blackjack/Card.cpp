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
}
