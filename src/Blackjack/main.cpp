#include <GameEngine.h>

#include "Deck.h"

#include "Card.h"

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init(600, 600);

    eng->Graphics->SetBackgroundColor(0x6495EDFF);

    Deck* x = new Deck(eng);

    x->SetupStandard52CardsDeck();

    x->ShuffleDeck();
    
    return 0;
}