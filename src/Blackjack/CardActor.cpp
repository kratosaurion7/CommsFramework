#include "CardActor.h"


#include <BaseSprite.h>
#include <BaseText.h>

#include "Deck.h"
#include "Card.h"

#include "CardActor.h"
#include <GameEngine.h>

CardActor::CardActor()
{
    Cards = new PointerList<Card*>();

    TotalLabel = Engine->CreateText("Card Total");
    TotalLabel->SetPos(450, 680);
    TotalLabel->SetColor(0xFFFFFFFF);
    TotalLabel->SetCharacterSize(16);

    TotalText = Engine->CreateText("0");
    TotalText->SetPos(450, 700);
    TotalLabel->Show(true);
    TotalText->Show(true);

    CardChoosingState = CardChoosing::IDLE;
    CardActorCurrentStatus = CardPlayerStatus::OK;
}


CardActor::~CardActor()
{
    delete(Cards);
}

int CardActor::CardsTotal()
{
    int totalValue = 0;

    auto it = Cards->GetContainer()->begin();
    while (it != Cards->GetContainer()->end())
    {
        Card* card = (*it);

        totalValue += card->CardValue;

        it++;
    }

    return totalValue;
}

void CardActor::ReceiveCard(Card * card)
{
    if (this->Cards->Count() > 0)
    {
        Card* lastCard = this->Cards->Last();
        card->cardBack->SetZIndexOverObject(lastCard->cardBack); // Card is the same as lastCard
        card->cardFront->SetZIndexOverObject(lastCard->cardFront);
    }

    this->Cards->Add(card);

    if (this->CardsTotal() > 21)
    {
        this->CardActorCurrentStatus = CardPlayerStatus::BUSTED;
    }
    else
    {
        this->CardActorCurrentStatus = CardPlayerStatus::OK;
    }
}

void CardActor::Update()
{
    BaseActor::Update();

    UpdateStatusTexts();

    UpdateCardPositions();
}

void CardActor::UpdateStatusTexts()
{
    std::string CardsTotal = std::to_string(this->CardsTotal());
    this->TotalText->SetText(CardsTotal);
}