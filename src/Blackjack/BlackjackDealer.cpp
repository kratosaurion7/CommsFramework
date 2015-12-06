#include "BlackjackDealer.h"



BlackjackDealer::BlackjackDealer()
{
    MoneyLabel->Show(false);
    Money->Show(false);

    LastBetLabel->Show(false);
    LastBet->Show(false);

    CurrentBetLabel->Show(false);
    CurrentBetText->Show(false);

    TotalLabel->Show(false);
    TotalText->Show(false);

}


BlackjackDealer::~BlackjackDealer()
{
}

bool BlackjackDealer::BlackjackIsPossible()
{
    // Let's say the first card is always the one shown to the player
    if (this->Cards->Get(0)->CardValue == Card::CARD_VALUE::Ace)
        return true;

    return false;
}

void BlackjackDealer::UpdateCardPositions()
{
}
