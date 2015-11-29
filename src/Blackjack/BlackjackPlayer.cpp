#include "BlackjackPlayer.h"



BlackjackPlayer::BlackjackPlayer()
{
    PlayerCards = new PointerList<Card*>();
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
