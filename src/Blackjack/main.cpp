#include <GameEngine.h>

#include "Deck.h"

#include "Card.h"

#include <LiteList.h>

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init(800, 800);

    eng->Graphics->SetBackgroundColor(0x6495EDFF);

    Deck* x = new Deck(eng);

    x->SetupStandard52CardsDeck();

    x->ShuffleDeck();

    while (true)
    {
        eng->Play();

        if (eng->Keyboard->IsKeyClicked(Key::Space))
        {
            x->ShuffleDeck();
        }

        if (eng->Keyboard->IsKeyClicked(Key::E))
        {
            x->SpreadCardsOnScreen();
        }

    }

    return 0;
}