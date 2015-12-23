#include "CardsShoe.h"

#include "Card.h"
#include "Deck.h"

#include <GameEngine.h> // TODO

CardsShoe::CardsShoe()
{
    Decks = new PointerList<Deck*>();

    DiscartPile = new PointerList<Card*>();

    this->Engine = GameEngine::GetInstance();
}

CardsShoe::~CardsShoe()
{
    this->Decks->Release();
    delete(this->Decks);
}

Card* CardsShoe::DrawCard()
{
    Deck* firstDeck = this->Decks->Get(0);

    Card* nextCard = firstDeck->DrawCard();
    DiscartPile->Add(nextCard);

    if (firstDeck->DeckCards->Count() == 0)
    {
        this->Decks->RemoveAt(0);

        if (this->Decks->Count() == 0)
        {
            // On each card draw, we check if the shoe is empty. This prevents ever trying to draw a card when there is none left.
            this->ReSeedDeck();
        }
    }

    return nextCard;
}

int CardsShoe::CardsLeft()
{
    int totalCards = 0;

    auto it = this->Decks->GetContainer()->begin();
    while (it != this->Decks->GetContainer()->end())
    {
        Deck* deck = (*it);
        
        totalCards += deck->DeckCards->Count();

        it++;
    }

    return totalCards;
}

void CardsShoe::ReSeedDeck(int amountOfDecks)
{
    this->DiscartPile->Release();

    this->Decks->Release();

    for (int i = 0; i < amountOfDecks; i++)
    {
        Deck* newDeck = new Deck(this->Engine);

        newDeck->SetupStandard52CardsDeck();
        newDeck->ShuffleDeck();

        this->Decks->Add(newDeck);
    }
}
