#include <BaseGraphicEngine.h>
#include <GameEngine.h>
#include <LiteList.h>

#include "Deck.h"
#include "Card.h"

#include "BlackjackGame.h"

#include <MessageDialog.h>
#include <SDLUtilities.h>

#include <StringList.h>

int main()
{
    StringList* x = new StringList();

    GameEngine* eng = new GameEngine();

    eng->Init(800, 800);

    //eng->Graphics->SetBackgroundColor(0x659CEFFF);
    eng->Graphics->SetBackgroundColor(101, 156, 239);

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

        if (eng->Keyboard->IsKeyClicked(Key::Space))
        {
            SaveTextAsBMP((SDLText*)game->gameDrawDialog->DialogText, "test.bmp");
        }

        //if (eng->Keyboard->IsKeyClicked(Key::E))
        //{
        //    x->SpreadCardsOnScreen();
        //}

    }

    return 0;
}