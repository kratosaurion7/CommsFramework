#include "BlackjackPlayer.h"



BlackjackPlayer::BlackjackPlayer()
{
    Engine = GameEngine::GetInstance();

    PlayerCards = new PointerList<Card*>();

    this->CurrentBet = 0;
    this->LastBet = 0;
    this->Money = 0;

    PlayerMoneyLabel = Engine->CreateText("Player Money");
    PlayerMoneyLabel->SetPos(0, 680);
    PlayerMoneyLabel->SetColor(0xFFFFFFFF);
    PlayerMoneyLabel->SetCharacterSize(16);

    PlayerMoney = Engine->CreateText("0");
    PlayerMoney->SetPos(0, 700);
    PlayerMoneyLabel->Show(true);
    PlayerMoney->Show(true);


    PlayerLastBetLabel = Engine->CreateText("Last bet");
    PlayerLastBetLabel->SetPos(150, 680);
    PlayerLastBetLabel->SetColor(0xFFFFFFFF);
    PlayerLastBetLabel->SetCharacterSize(16);


    PlayerLastBet = Engine->CreateText("0");
    PlayerLastBet->SetPos(150, 700);
    PlayerLastBetLabel->Show(true);
    PlayerLastBet->Show(true);


    CurrentBetLabel = Engine->CreateText("Current Bet");
    CurrentBetLabel->SetPos(300, 680);
    CurrentBetLabel->SetColor(0xFFFFFFFF);
    CurrentBetLabel->SetCharacterSize(16);

    CurrentBetText = Engine->CreateText("0");
    CurrentBetText->SetPos(300, 700);
    CurrentBetLabel->Show(true);
    CurrentBetText->Show(true);


    PlayerTotalLabel = Engine->CreateText("Card Total");
    PlayerTotalLabel->SetPos(450, 680);
    PlayerTotalLabel->SetColor(0xFFFFFFFF);
    PlayerTotalLabel->SetCharacterSize(16);

    PlayerTotalText = Engine->CreateText("0");
    PlayerTotalText->SetPos(450, 700);
    PlayerTotalLabel->Show(true);
    PlayerTotalText->Show(true);

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

void BlackjackPlayer::ReceiveCard(Card * card)
{
    this->PlayerCards->Add(card);

    if (this->CardsTotal() > 21)
    {
        this->PlayerStatus = PlayerStatus::BUSTED;
    }
    else
    {
        this->PlayerStatus = PlayerStatus::OK;
    }
}

void BlackjackPlayer::Update()
{
    UpdatePlayerStatusTexts();

    UpdateCardPositions();
}

void BlackjackPlayer::UpdatePlayerStatusTexts()
{
    this->PlayerMoney->SetText(std::to_string(Money));
    this->PlayerLastBet->SetText(std::to_string(LastBet));
    this->CurrentBetText->SetText(std::to_string(CurrentBet));
    
    std::string playerCardsTotal = std::to_string(this->CardsTotal());
    this->PlayerTotalText->SetText(playerCardsTotal);
}

void BlackjackPlayer::UpdateCardPositions()
{
    int cardIndex = 0;

    auto it = this->PlayerCards->GetContainer()->begin();
    while (it != this->PlayerCards->GetContainer()->end())
    {
        Card* cardIter = (*it);

        FPosition cardPos;
        cardPos.X = 200 + (100 * cardIndex);
        cardPos.Y = 400;

        cardIter->cardFront->SetPos(cardPos);
        cardIter->cardFront->Show(true);
        cardIter->cardFront->SetZIndex(cardIndex);

        it++;
        cardIndex++;
    }
}
