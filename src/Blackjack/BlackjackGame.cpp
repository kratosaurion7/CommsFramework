#include "BlackjackGame.h"



BlackjackGame::BlackjackGame()
{
    BaseActor::BaseActor();

    GameCards = new CardsShoe();
}


BlackjackGame::~BlackjackGame()
{
    delete(GameCards);
}

void BlackjackGame::Update()
{
    switch (this->GameState)
    {
        case START:
        {
            // Do game presentation, prompts for options, only the RESET state comes back here

            this->GameState = CHOOSE_BET;

            break;
        }
        case CHOOSE_BET:
        {
            break;
        }

        default:
            break;
    }
}
