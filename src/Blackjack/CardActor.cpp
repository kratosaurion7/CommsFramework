#include "CardActor.h"

CardActor::CardActor()
{
    Cards = new PointerList<Card*>();

    MoneyLabel = Engine->CreateText(" Money");
    MoneyLabel->SetPos(0, 680);
    MoneyLabel->SetColor(0xFFFFFFFF);
    MoneyLabel->SetCharacterSize(16);

    Money = Engine->CreateText("0");
    Money->SetPos(0, 700);
    MoneyLabel->Show(true);
    Money->Show(true);


    LastBetLabel = Engine->CreateText("Last bet");
    LastBetLabel->SetPos(150, 680);
    LastBetLabel->SetColor(0xFFFFFFFF);
    LastBetLabel->SetCharacterSize(16);


    LastBet = Engine->CreateText("0");
    LastBet->SetPos(150, 700);
    LastBetLabel->Show(true);
    LastBet->Show(true);


    CurrentBetLabel = Engine->CreateText("Current Bet");
    CurrentBetLabel->SetPos(300, 680);
    CurrentBetLabel->SetColor(0xFFFFFFFF);
    CurrentBetLabel->SetCharacterSize(16);

    CurrentBetText = Engine->CreateText("0");
    CurrentBetText->SetPos(300, 700);
    CurrentBetLabel->Show(true);
    CurrentBetText->Show(true);


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
    UpdateStatusTexts();

    UpdateCardPositions();
}

void CardActor::UpdateStatusTexts()
{
    std::string CardsTotal = std::to_string(this->CardsTotal());
    this->TotalText->SetText(CardsTotal);
}