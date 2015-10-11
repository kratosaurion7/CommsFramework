#include <GameEngine.h>

#include <BaseActor.h>

#include "GameGrid.h"

int main()
{
    GameEngine* x = new GameEngine();

    x->Init(600, 600);

    x->Graphics->SetBackgroundColor(0x00FFFFFF);


    //BaseSprite* blockSprite = x->CreateSprite("Block_01");
    //BaseTexture* tex = x->Graphics->CreateTexture();
    //tex->Initalize(128, 128);
    //tex->SetSolidColor(0xFF0000FF);
    //blockSprite->SetTexture(tex);

    //BaseActor* act = x->CreateActor(blockSprite);
    //act->BindControls(WASD);

    GameGrid* grid = new GameGrid(5);
    x->AttachActor(grid);

    grid->Setup();

    while (true)
    {
        if (x->Keyboard->IsKeyPressed(_Escape))
            break;

        //if (x->Keyboard->IsKeyPressed(Space))
        //    act->Sprites->Get(0)->ResetOffsets();

        x->Play();
    }

    return 0;
}