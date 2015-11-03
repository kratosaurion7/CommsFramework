#include <GameEngine.h>

#include <BaseActor.h>

#include "GameGrid.h"

int main()
{
    GameEngine* x = new GameEngine();

    x->Init(600, 600);

    x->Graphics->SetBackgroundColor(0x6495EDFF);

    GameGrid* grid = new GameGrid(5, x);
    x->AttachActor(grid);

    grid->Setup();

    while (true)
    {
        if (x->Keyboard->IsKeyPressed(_Escape))
            break;

        x->Play();
    }

    delete(x);

    return 0;
}