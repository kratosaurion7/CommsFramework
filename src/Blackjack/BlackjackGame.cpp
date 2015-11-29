#include "BlackjackGame.h"



BlackjackGame::BlackjackGame()
{
    GameCards = new CardsShoe();
}


BlackjackGame::~BlackjackGame()
{
    delete(GameCards);
}

void BlackjackGame::Process_State()
{

}
