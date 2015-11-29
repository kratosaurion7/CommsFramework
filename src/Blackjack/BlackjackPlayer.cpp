#include "BlackjackPlayer.h"



BlackjackPlayer::BlackjackPlayer()
{
    PlayerCards = new PointerList<Card*>();

    this->CurrentBet = 0;
    this->LastBet = 0;
    this->Money = 0;
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
