#include "Deck.h"



Deck::Deck()
{
}


Deck::~Deck()
{
}

void Deck::ShuffleDeck()
{
    this->DeckCards->Shuffle();
}

Card * Deck::DrawCard()
{
    return nullptr;
}
