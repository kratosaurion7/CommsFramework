#include "CardsShoe.h"



CardsShoe::CardsShoe()
{
    Decks = new PointerList<Deck*>();

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

    if (firstDeck->DeckCards->Count() == 0)
    {
        this->Decks->RemoveAt(0);

        if (this->Decks->Count() == 0)
        {
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
    for (int i = 0; i < amountOfDecks; i++)
    {
        Deck* newDeck = new Deck(this->Engine);

        newDeck->SetupStandard52CardsDeck();
        newDeck->ShuffleDeck();

        this->Decks->Add(newDeck);
    }
}
