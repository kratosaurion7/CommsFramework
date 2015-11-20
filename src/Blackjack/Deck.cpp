#include "Deck.h"



Deck::Deck()
{
    this->DeckCards = new PointerList<Card*>();
}


Deck::~Deck()
{
}

void Deck::SetupStandard52CardsDeck()
{
    for (int i = 0; i < Card::CARD_SUITS_COUNT; i++)
    {
        for (int k = 0; k < Card::CARD_VALUE_COUNT; k++)
        {
            Card* newCard = new Card();

            newCard->CardSuit = (Card::CARD_SUITS)i;
            newCard->CardValue = (Card::CARD_VALUE)k;

            this->DeckCards->Add(newCard);
        }
    }
}

void Deck::ShuffleDeck()
{
    this->DeckCards->Shuffle();
}

Card * Deck::DrawCard()
{
    return nullptr;
}
