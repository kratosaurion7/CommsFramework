#include "Deck.h"

Deck::Deck(GameEngine* engine)
{
    Engine = engine;

    this->DeckCards = new BaseStack<Card*>();
}

Deck::~Deck()
{
    //this->DeckCards->Release();

    delete(this->DeckCards);
}

void Deck::SetupStandard52CardsDeck()
{
    for (int i = 0; i < Card::CARD_SUITS_COUNT; i++)
    {
        for (int k = 1; k < Card::CARD_VALUE_COUNT; k++)
        {
            Card* newCard = new Card();

            newCard->CardSuit = (Card::CARD_SUITS)i;
            newCard->CardValue = (Card::CARD_VALUE)k;

            SetupCardSprites(newCard);

            this->DeckCards->Push(newCard);
        }
    }
}

void Deck::ShuffleDeck()
{
    this->DeckCards->Shuffle();
}

Card* Deck::DrawCard()
{
    Card* drawn = this->DeckCards->Pop();

    return drawn;
}

void Deck::SetupCardSprites(Card * targetCard)
{
    char* cardBackName = "cardBack_blue1.png\0";
    char cardFileName[256];
    char* suitName;
    char* cardValue;

    switch (targetCard->CardSuit)
    {
        case Card::SPADES:
        {
            suitName = "Spades";
            break;
        }
        case Card::HEARTS:
        {
            suitName = "Hearts";
            break;
        }
        case Card::DIAMOND:
        {
            suitName = "Diamonds";
            break;
        }
        case Card::CLUBS:
        {
            suitName = "Clubs";
            break;
        }
        default:
        {
            suitName = "?SuitName?";
            break;
        }
    }

    cardValue = new char[256];
    cardValue[0] = 0;

    if (targetCard->CardValue < Card::Jack)
    {
        sprintf_s(cardValue, 256, "%d", targetCard->CardValue);
    }
    else
    {
        switch (targetCard->CardValue)
        {
            case Card::Jack:
            {
                sprintf_s(cardValue, 256, "%s", "J");
                break;
            }
            case Card::Queen:
            {
                sprintf_s(cardValue, 256, "%s", "Q");
                break;
            }
            case Card::King:
            {
                sprintf_s(cardValue, 256, "%s", "K");
            }
        default:
            break;
        }
    }

    sprintf_s(cardFileName, 256, "card%s%s.png\0", suitName, cardValue);

    std::string cardBackFileName = "assets\\cards\\back\\";
    cardBackFileName.append(cardBackName);

    std::string cardFrontFileName = "assets\\cards\\front\\";
    cardFrontFileName.append(cardFileName);

    targetCard->cardBack = Engine->CreateSprite("CardBack", cardBackFileName);
    targetCard->cardFront = Engine->CreateSprite("CardFront", cardFrontFileName);

}
