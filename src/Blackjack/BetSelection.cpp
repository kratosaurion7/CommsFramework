#include "BetSelection.h"



BetSelection::BetSelection()
{
    BaseActor::BaseActor();

    this->BetOne = this->Engine->CreateSprite("BetOneToken");
    this->BetFive = this->Engine->CreateSprite("BetFiveToken");
    this->BetTen = this->Engine->CreateSprite("BetTenToken");
    this->BetTwentyFive = this->Engine->CreateSprite("BetTwentyFiveToken");
    this->BetOneHundred = this->Engine->CreateSprite("BetOneHundredToken");

    this->TotalBetText = this->Engine->CreateText("0");
    this->TotalBetText->SetCharacterSize(36);
    this->TotalBetText->SetColor(0xFFFFFFFF);
    this->TotalBetText->SetPos(650, 0);
    this->TotalBetText->Show(true); // May relocate this member elsewhere.

    this->ButtonAccept = this->Engine->CreateSprite("BetButtonAccept");
    this->ButtonReset  = this->Engine->CreateSprite("BetButtonReset");

    BettedLevels = new BaseList<BetLevels>();

    this->Sprites->Add(this->BetOne);
    this->Sprites->Add(this->BetFive);
    this->Sprites->Add(this->BetTen);
    this->Sprites->Add(this->BetTwentyFive);
    this->Sprites->Add(this->BetOneHundred);
    this->Sprites->Add(this->TotalBetText);
    this->Sprites->Add(this->ButtonAccept);
    this->Sprites->Add(this->ButtonReset);

    this->BetOne->SetTexture("assets//tokens//1.png");
    this->BetOne->SetPos(0, 0);

    this->BetFive->SetTexture("assets//tokens//5.png");
    this->BetFive->SetPos(105, 0);

    this->BetTen->SetTexture("assets//tokens//10.png");
    this->BetTen->SetPos(210, 0);

    this->BetTwentyFive->SetTexture("assets//tokens//25.png");
    this->BetTwentyFive->SetPos(315, 0);

    this->BetOneHundred->SetTexture("assets//tokens//100.png");
    this->BetOneHundred->SetPos(420, 0);

    this->ButtonAccept->SetTexture("assets//buttons//AcceptBet.png");
    this->ButtonAccept->SetPos(0, 105);

    this->ButtonReset->SetTexture("assets//buttons//ResetBet.png");
    this->ButtonReset->SetPos(155, 105);

    this->BettingState = IDLE;
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

void BetSelection::ResetBet()
{
    this->BettedLevels->Clear();

    UpdateTotalBet();
}

void BetSelection::StartBetSelection()
{
    BetOne->Show(true);
    BetFive->Show(true);
    BetTen->Show(true);
    BetTwentyFive->Show(true);
    BetOneHundred->Show(true);
    ButtonAccept->Show(true);
    ButtonReset->Show(true);

    this->BettingState = BetSelection::BetSelectState::NEED_SELECTION;
}

void BetSelection::StopBetSelection()
{
    BetOne->Show(false);
    BetFive->Show(false);
    BetTen->Show(false);
    BetTwentyFive->Show(false);
    BetOneHundred->Show(false);
    ButtonAccept->Show(false);
    ButtonReset->Show(false);

    this->BettingState = BetSelection::BetSelectState::FINISHED;
}

void BetSelection::ShowAll()
{
    this->Sprites->ForEach([](DrawObject* p) { p->Show(true); });
}

void BetSelection::HideAll()
{
    this->Sprites->ForEach([](DrawObject* p) { p->Show(false); });
}

void BetSelection::Update()
{
    switch (BettingState)
    {
        case BetSelection::IDLE:
            break;
        case BetSelection::NEED_SELECTION:
        {
            if (this->ButtonAccept->Clicked())
            {
                this->BettingState = FINISHED;
            }

            if (this->BetOne->Clicked())
                this->PlaceBet(BetSelection::BetLevels::One);
            
            if (this->BetFive->Clicked())
                this->PlaceBet(BetSelection::BetLevels::Five);

            if (this->BetTen->Clicked())
                this->PlaceBet(BetSelection::BetLevels::Ten);

            if (this->BetTwentyFive->Clicked())
                this->PlaceBet(BetSelection::BetLevels::TwentyFive);

            if (this->BetOneHundred->Clicked())
                this->PlaceBet(BetSelection::BetLevels::OneHundred);

            if (this->ButtonReset->Clicked())
                this->ResetBet();

            break;
        }
        case BetSelection::FINISHED:
        {
            break;
        }
        default:
            break;
    }
}

void BetSelection::UpdateTotalBet()
{
    int total = 0;

    auto it = this->BettedLevels->GetContainer()->begin();
    while (it != this->BettedLevels->GetContainer()->end())
    {
        BetLevels level = (*it);

        total += level;

        it++;
    }

    this->TotalBetText->SetText(std::to_string(total));
}
