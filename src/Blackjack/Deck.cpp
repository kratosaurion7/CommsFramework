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
    this->DeckCards->Clear();

    for (int i = 0; i < Card::CARD_SUITS_COUNT; i++)
    {
        for (int k = 1; k < Card::CARD_VALUE_COUNT; k++)
        {
            Card* newCard = new Card();

            newCard->CardSuit = (Card::CARD_SUITS)i;
            newCard->CardValue = (Card::CARD_VALUE)k;

            std::string cardFrontStringName;
            cardFrontStringName.append(std::to_string(i));
            cardFrontStringName.append("_");
            cardFrontStringName.append(std::to_string(k));

            newCard->cardBack = Engine->CreateSprite("CardBack");
            newCard->cardFront = Engine->CreateSprite(cardFrontStringName);

            SetupCardSprites(newCard);

            this->DeckCards->Push(newCard);

            Engine->AttachActor(newCard);
        }
    }
}

void Deck::ShuffleDeck()
{
    this->DeckCards->Shuffle();

    this->AssignCardSprites();

    this->PositionCards();
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
    char suitName[256];
    char cardValue[256];

    switch (targetCard->CardSuit)
    {
        case Card::SPADES:
        {
            sprintf_s(suitName, 256, "%s", "Spades");
            break;
        }
        case Card::HEARTS:
        {
            sprintf_s(suitName, 256, "%s", "Hearts");
            break;
        }
        case Card::DIAMOND:
        {
            sprintf_s(suitName, 256, "%s", "Diamonds");
            break;
        }
        case Card::CLUBS:
        {
            sprintf_s(suitName, 256, "%s", "Clubs");
            break;
        }
        default:
        {
            sprintf_s(suitName, 256, "%s", "?SuitName?");
            break;
        }
    }

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
                break;
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

    targetCard->cardBack->SetTexture(cardBackFileName);
    targetCard->cardFront->SetTexture(cardFrontFileName);
}

void Deck::AssignCardSprites()
{
    auto it = DeckCards->GetContainer()->begin();
    auto end = DeckCards->GetContainer()->end();

    while (it != end)
    {
        Card* item = (*it);

        SetupCardSprites(item);

        it++;
    }
}

void Deck::PositionCards()
{
    auto end = this->DeckCards->GetContainer()->end();
    auto it = this->DeckCards->GetContainer()->begin();

    int index = 0;
    int nextX = 0;
    int nextY = 0;
    while (it != end)
    {
        Card* item = (*it);

        item->cardFront->SetPos(nextX, nextY);
        item->cardBack->Show(false);
        item->cardFront->Show(true);
        item->cardFront->SetZIndex(index);
        nextX += 50;

        index++;
        if (index % 10 == 0)
        {
            nextX = 0;
            nextY += 100;
        }

        it++;
    }

}
