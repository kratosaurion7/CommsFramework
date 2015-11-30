#include "BlackjackPlayer.h"



BlackjackPlayer::BlackjackPlayer()
{
    PlayerCards = new PointerList<Card*>();

    this->CurrentBet = 0;
    this->LastBet = 0;
    this->Money = 0;

    CardChoosingState = CardChoosing::IDLE;
}


BlackjackPlayer::~BlackjackPlayer()
{
    delete(this->PlayerCards);
}

int BlackjackPlayer::CardsTotal()
{
    int totalValue = 0;

    auto it = PlayerCards->GetContainer()->begin();
    while (it != PlayerCards->GetContainer()->end())
    {
        Card* card = (*it);

        totalValue += card->CardValue;

        it++;
    }

    return totalValue;
}

bool BlackjackPlayer::CanSplit()
{
    // Confirm if can split when card 0 = 10 and card 1 = Jack/Queen/King
    if (this->PlayerCards->Get(0)->CardValue == this->PlayerCards->Get(1)->CardValue)
        return true;

    return false;
}
