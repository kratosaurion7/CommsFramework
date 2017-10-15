#include "Deck.h"

#include <stdio.h>
#include <GameEngine.h>
#include <BaseSprite.h>
#include <BaseList.h>


#include "Card.h"


Deck::Deck(GameEngine* engine)
{
    Engine = engine;

    this->DeckCards = new BaseStack<Card*>();
}

Deck::~Deck()
{
    //this->DeckCards->Release();

    auto it = this->DeckCards->GetContainer()->begin();
    while (it != this->DeckCards->GetContainer()->end())
    {
        delete *it;

        it++;
    }
    
    this->DeckCards->Clear();
    delete(this->DeckCards);

    Engine->DetachActor(this);
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

            switch (k)
            {
                case 11:
                case 12:
                case 13:
                    newCard->CardCountValue = 10;
                    break;
                case 1:
                    newCard->CardCountValue = 11;
                default:
                    newCard->CardCountValue = k;
                    break;
            }

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

void Deck::SetupTestAcesDeck()
{
    // Set initial player cards
    Card* cardOne = new Card();
    cardOne->CardSuit = Card::CARD_SUITS::SPADES;
    cardOne->CardValue = Card::CARD_VALUE::Jack;
    cardOne->CardCountValue = 10;
    cardOne->cardBack = Engine->CreateSprite();
    cardOne->cardFront = Engine->CreateSprite();

    Card* cardTwo= new Card();
    cardTwo->CardSuit = Card::CARD_SUITS::SPADES;
    cardTwo->CardValue = Card::CARD_VALUE::Ace;
    cardTwo->CardCountValue = 11;
    cardTwo->cardBack = Engine->CreateSprite();
    cardTwo->cardFront = Engine->CreateSprite();

    SetupCardSprites(cardOne);
    SetupCardSprites(cardTwo);

    // Set Dealer cards
    Card* cardThree= new Card();
    cardThree->CardSuit = Card::CARD_SUITS::SPADES;
    cardThree->CardValue = Card::CARD_VALUE::Ace;
    cardThree->CardCountValue = 11;
    cardThree->cardBack = Engine->CreateSprite();
    cardThree->cardFront = Engine->CreateSprite();

    Card* cardFour= new Card();
    cardFour->CardSuit = Card::CARD_SUITS::SPADES;
    cardFour->CardValue = Card::CARD_VALUE::Ace;
    cardFour->CardCountValue = 11;
    cardFour->cardBack = Engine->CreateSprite();
    cardFour->cardFront = Engine->CreateSprite();

    SetupCardSprites(cardThree);
    SetupCardSprites(cardFour);

    // Setup next cards
    Card* cardFive= new Card();
    cardFive->CardSuit = Card::CARD_SUITS::SPADES;
    cardFive->CardValue = Card::CARD_VALUE::Four;
    cardFive->CardCountValue = 4;
    cardFive->cardBack = Engine->CreateSprite();
    cardFive->cardFront = Engine->CreateSprite();

    Card* cardSix= new Card();
    cardSix->CardSuit = Card::CARD_SUITS::SPADES;
    cardSix->CardValue = Card::CARD_VALUE::King;
    cardSix->CardCountValue = 10;
    cardSix->cardBack = Engine->CreateSprite();
    cardSix->cardFront = Engine->CreateSprite();

    SetupCardSprites(cardFive);
    SetupCardSprites(cardSix);

    this->DeckCards->Push(cardThree);
    this->DeckCards->Push(cardFour);
    this->DeckCards->Push(cardFive);
    this->DeckCards->Push(cardSix);
    this->DeckCards->Push(cardOne);
    this->DeckCards->Push(cardTwo);


    Engine->AttachActor(cardOne);
    Engine->AttachActor(cardTwo);
    Engine->AttachActor(cardThree);
    Engine->AttachActor(cardFour);
    Engine->AttachActor(cardFive);
    Engine->AttachActor(cardSix);
}

void Deck::ShuffleDeck()
{
    this->DeckCards->Shuffle();

    this->AssignCardSprites();
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
            snprintf(suitName, 256, "%s", "Spades");
            break;
        }
        case Card::HEARTS:
        {
            snprintf(suitName, 256, "%s", "Hearts");
            break;
        }
        case Card::DIAMOND:
        {
            snprintf(suitName, 256, "%s", "Diamonds");
            break;
        }
        case Card::CLUBS:
        {
            snprintf(suitName, 256, "%s", "Clubs");
            break;
        }
        default:
        {
            snprintf(suitName, 256, "%s", "?SuitName?");
            break;
        }
    }

    if (targetCard->CardValue < Card::Jack)
    {
        snprintf(cardValue, 256, "%d", targetCard->CardValue);
    }
    else
    {
        switch (targetCard->CardValue)
        {
            case Card::Jack:
            {
                snprintf(cardValue, 256, "%s", "J");
                break;
            }
            case Card::Queen:
            {
                snprintf(cardValue, 256, "%s", "Q");
                break;
            }
            case Card::King:
            {
                snprintf(cardValue, 256, "%s", "K");
                break;
            }
            default:
                break;
        }
    }

    snprintf(cardFileName, 256, "card%s%s.png\0", suitName, cardValue);

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

void Deck::SpreadCardsOnScreen()
{
    auto end = this->DeckCards->GetContainer()->end();
    auto it = this->DeckCards->GetContainer()->begin();

    int index = 0;
    float nextX = 0;
    float nextY = 0;
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
