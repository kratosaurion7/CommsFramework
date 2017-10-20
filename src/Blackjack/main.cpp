#include <BaseGraphicEngine.h>
#include <GameEngine.h>
#include <LiteList.h>

#include "Deck.h"
#include "Card.h"

#include "BlackjackGame.h"

#include "PlayerControls.h"

#include <MessageDialog.h>
#include <SDLUtilities.h>

#include <FileSave.h>

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init(800, 800);

    
    eng->Graphics->SetBackgroundColor(101, 156, 239);

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
            eng->Graphics->Scale(0.5);
        }
    }

    return 0;
}