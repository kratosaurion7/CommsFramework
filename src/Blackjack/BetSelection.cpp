#include "BetSelection.h"



BetSelection::BetSelection()
{
    BaseActor::BaseActor();

    this->BetOne = this->Engine->CreateSprite("BetOneToken");
    this->BetFive = this->Engine->CreateSprite("BetFiveToken");
    this->BetTen = this->Engine->CreateSprite("BetTenToken");
    this->BetTwentyFive = this->Engine->CreateSprite("BetTwentyFiveToken");
    this->BetOneHundred = this->Engine->CreateSprite("BetOneHundredToken");

    this->TotalBet = this->Engine->CreateText("0");

    this->ButtonAccept = this->Engine->CreateSprite("BetButtonAccept");
    this->ButtonCancel = this->Engine->CreateSprite("BetButtonCancel");

    BettedLevels = new BaseList<BetLevels>();

    this->Sprites->Add(this->BetOne);
    this->Sprites->Add(this->BetFive);
    this->Sprites->Add(this->BetTen);
    this->Sprites->Add(this->BetTwentyFive);
    this->Sprites->Add(this->BetOneHundred);
    this->Sprites->Add(this->TotalBet);
    this->Sprites->Add(this->ButtonAccept);
    this->Sprites->Add(this->ButtonCancel);

    this->BetOne->SetTexture("assets//tokens//1.png");
    this->BetFive->SetTexture("assets//tokens//5.png");
    this->BetTen->SetTexture("assets//tokens//10.png");
    this->BetTwentyFive->SetTexture("assets//tokens//25.png");
    this->BetOneHundred->SetTexture("assets//tokens//100.png");

    this->ButtonAccept->SetTexture("assets//buttons//AcceptBet");
    this->ButtonCancel->SetTexture("assets//buttons//CancelBet");
}


BetSelection::~BetSelection()
{
    BettedLevels->Clear();
    
    delete(BettedLevels);
}

void BetSelection::PlaceBet(BetSelection::BetLevels level)
{
    BettedLevels->Add(level);

    switch (level) // Animate the token when betted
    {
        case BetSelection::One:
            break;
        case BetSelection::Five:
            break;
        case BetSelection::Ten:
            break;
        case BetSelection::TwentyFive:
            break;
        case BetSelection::OneHundred:
            break;
        default:
            break;
    }

    UpdateTotalBet();
}

void BetSelection::RemoveBet(BetSelection::BetLevels level)
{
    BettedLevels->RemoveObject(level);

    UpdateTotalBet();
}

void BetSelection::ShowBetSelection()
{
    BetOne->Show(true);
    BetFive->Show(true);
    BetTen->Show(true);
    BetTwentyFive->Show(true);
    BetOneHundred->Show(true);
    ButtonAccept->Show(true);
    ButtonCancel->Show(true);
}

void BetSelection::HideBetSelection()
{
    BetOne->Show(false);
    BetFive->Show(false);
    BetTen->Show(false);
    BetTwentyFive->Show(false);
    BetOneHundred->Show(false);
    ButtonAccept->Show(false);
    ButtonCancel->Show(false);
}

void BetSelection::ShowAll()
{
    this->Sprites->ForEach([](DrawObject* p) { p->Show(true); });
}

void BetSelection::HideAll()
{
    this->Sprites->ForEach([](DrawObject* p) { p->Show(false); });
}

void BetSelection::UpdateTotalBet()
{
    int total;

    auto it = this->BettedLevels->GetContainer()->begin();
    while (it != this->BettedLevels->GetContainer()->end())
    {
        BetLevels level = (*it);

        total += level;

        it++;
    }

    this->TotalBet->SetText(std::to_string(total));
}
