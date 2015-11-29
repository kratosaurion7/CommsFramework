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

    BettedLevels = new BaseList<BetLevels>();

    this->Sprites->Add(this->BetOne);
    this->Sprites->Add(this->BetFive);
    this->Sprites->Add(this->BetTen);
    this->Sprites->Add(this->BetTwentyFive);
    this->Sprites->Add(this->BetOneHundred);
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
