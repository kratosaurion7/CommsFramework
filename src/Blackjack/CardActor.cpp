#include "CardActor.h"


#include <Graphic/Base Classes/BaseSprite.h>
#include <Graphic/Base Classes/BaseText.h>
#include <Engine/GameEngine.h>

#include "Deck.h"
#include "Card.h"
#include "CardHand.h"
#include "CardActor.h"


CardActor::CardActor()
{
    Hands = new PointerList<CardHand*>();

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
    delete(Hands);
}

int CardActor::CardsTotal(int handIndex)
{
    int totalValue = 0;

    CardHand* hand = Hands->Get(handIndex);

    totalValue = CardsTotal(hand);

    return totalValue;
}

int CardActor::CardsTotal(CardHand* targetHand)
{
    int totalValue = 0;

    if (targetHand != NULL)
    {
        totalValue = targetHand->GetTotal();
    }

    return totalValue;
}

void CardActor::ReceiveCard(Card* card, int handIndex)
{
    CardHand* selectedHand = Hands->Get(handIndex);

    this->ReceiveCard(card, selectedHand);
}

void CardActor::ReceiveCard(Card* card, CardHand* targetHand)
{
    CardHand* selectedHand = targetHand;

    if (selectedHand == NULL)
        return;

    selectedHand->Cards->Add(card);

    if (selectedHand->Cards->Count() > 0)
    {
        Card* previousCard = selectedHand->Cards->Get(0);

        for (int i = 1; i < selectedHand->Cards->Count(); i++)
        {
            Card* currentCard = selectedHand->Cards->Get(i);

            currentCard->cardBack->SetZIndexOverObject(previousCard->cardBack);
            currentCard->cardFront->SetZIndexOverObject(previousCard->cardFront);

            previousCard = currentCard;
        }
    }


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

void CardActor::RevealCards()
{
    auto it = this->Hands->GetContainer()->begin();
    while (it != this->Hands->GetContainer()->end())
    {
        CardHand* hand = (*it);

        auto cardIt = hand->Cards->GetContainer()->begin();
        while (cardIt != hand->Cards->GetContainer()->end())
        {
            Card* card = (*cardIt);
            card->TurnUp();

            cardIt++;
        }

        it++;
    }
}

void CardActor::HideCards()
{
    auto it = this->Hands->GetContainer()->begin();
    while (it != this->Hands->GetContainer()->end())
    {
        CardHand* hand = (*it);

        auto cardIt = hand->Cards->GetContainer()->begin();
        while (cardIt != hand->Cards->GetContainer()->end())
        {
            Card* card = (*cardIt);
            card->TurnDown();

            cardIt++;
        }

        it++;
    }
}

void CardActor::ClearCards()
{
    auto it = this->Hands->GetContainer()->begin();
    while (it != this->Hands->GetContainer()->end())
    {
        CardHand* hand = (*it);

        auto cardIt = hand->Cards->GetContainer()->begin();
        while (cardIt != hand->Cards->GetContainer()->end())
        {
            Card* card = (*cardIt);
            card->cardBack->Show(false);
            card->cardFront->Show(false);

            cardIt++;
        }

        hand->Cards->Clear();

        it++;
    }

    Hands->Clear();
}

void CardActor::UpdateStatusTexts()
{
    std::string CardsTotal = std::to_string(this->CardsTotal());
    this->TotalText->SetText(CardsTotal);
}