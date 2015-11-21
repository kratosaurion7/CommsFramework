#include <GameEngine.h>

#include "Deck.h"

#include "Card.h"

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init(800, 800);

    eng->Graphics->SetBackgroundColor(0x6495EDFF);

    Deck* x = new Deck(eng);

    x->SetupStandard52CardsDeck();

    x->ShuffleDeck();

    auto end = x->DeckCards->GetContainer()->end();
    auto it = x->DeckCards->GetContainer()->begin();

    int index = 0;
    int nextX = 0;
    int nextY = 0;
    while (it != end)
    {
        Card* item = (*it);

        eng->AttachActor(item);

        item->cardFront->SetPos(nextX, nextY);
        item->cardBack->Show(false);
        item->cardFront->Show(true);
        item->cardFront->SetZIndex(index);
        nextX += 50;

        index++;
        if (index % 10 == 0)
        {
            nextX = 0;
            nextY += 100;
        }
        
        it++;
    }

    while (true)
    {
        eng->Play();

        if (eng->Keyboard->IsKeyClicked(Key::Space))
        {
            x->ShuffleDeck();
        }

    }

    return 0;
}