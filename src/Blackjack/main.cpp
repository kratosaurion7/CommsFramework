#include <GameEngine.h>
#include <LiteList.h>

#include "Deck.h"
#include "Card.h"

#include "BlackjackGame.h"

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init(800, 800);

    eng->Graphics->SetBackgroundColor(0x6495EDFF);

    //Deck* x = new Deck(eng);

    //x->SetupStandard52CardsDeck();

    //x->ShuffleDeck();

    BlackjackGame* game = new BlackjackGame();
    eng->AttachActor(game);

    while (true)
    {
        eng->Play();

        if (eng->Keyboard->IsKeyClicked(Key::_Escape))
        {
            break;
        }

        //if (eng->Keyboard->IsKeyClicked(Key::E))
        //{
        //    x->SpreadCardsOnScreen();
        //}

    }

    return 0;
}