#include <Graphic/Base Classes/BaseGraphicEngine.h>
#include <Engine/GameEngine.h>

#include "Deck.h"

#include "BlackjackGame.h"

GameEngine* eng;

void play_one();

#ifdef __EMSCRIPTEN__

#include <emscripten.h>

#endif


int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init(800, 800);

    
    eng->Graphics->SetBackgroundColor(101, 156, 239);

    BlackjackGame* game = new BlackjackGame();
    eng->AttachActor(game);

#ifdef __EMSCRIPTEN__

    emscripten_set_main_loop(play_one, 30, 0);

#else
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
#endif

    return 0;
}

void play_one()
{
    eng->Play();

    if (eng->Keyboard->IsKeyClicked(Key::_Escape))
    {
        return;
    }

    if (eng->Keyboard->IsKeyClicked(Key::Space))
    {
        //eng->Graphics->Scale(0.5);
    }
}