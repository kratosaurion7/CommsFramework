#include "BlackjackPlayer.h"



BlackjackPlayer::BlackjackPlayer()
{
    this->CurrentBet = 0;
    this->LastBet = 0;
    this->Money = 0;
}


BlackjackPlayer::~BlackjackPlayer()
{
}

bool BlackjackPlayer::CanSplit()
{
    // Confirm if can split when card 0 = 10 and card 1 = Jack/Queen/King
    if (this->Cards->Get(0)->CardValue == this->Cards->Get(1)->CardValue)
        return true;

    return false;
}

void BlackjackPlayer::UpdateCardPositions()
{
    int cardIndex = 0;

    auto it = this->Cards->GetContainer()->begin();
    while (it != this->Cards->GetContainer()->end())
    {
        Card* cardIter = (*it);

        FPosition cardPos;
        cardPos.X = 200 + (100 * cardIndex);
        cardPos.Y = 400;

        cardIter->cardFront->SetPos(cardPos);
        cardIter->cardFront->Show(true);
        //cardIter->cardFront->SetZIndex(cardIndex);

        cardIter->cardBack->SetPos(cardPos);
        cardIter->cardBack->Show(false);
        //cardIter->cardBack->SetZIndex(cardIndex);

        it++;
        cardIndex++;
    }

}
