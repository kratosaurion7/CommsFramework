#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <PointerList.h>

#include "GameCore.h"
#include "GameButton.h"


int main()
{
    GameEngine* Engine = new GameEngine();
    Engine->Init(NB_TILES_W * TILE_W * TILE_SCALE, NB_TILES_H * TILE_H * TILE_SCALE);

    PointerList<GameButton*>* list = new PointerList<GameButton*>();

    int index = 0;
    for (int i = 0; i < NB_TILES_H; i++)
    {
        for (int j = 0; j < NB_TILES_W; j++)
        {
            GameButton* newBut = new GameButton();
            newBut->TileSprite->SetPos((int)(j * TILE_TOTAL_W), (int)(i * TILE_TOTAL_H));
            newBut->Index = index;
            newBut->PosX = j;
            newBut->PosY = i;

            list->Add(newBut);

            Engine->AttachActor(newBut);

            index++;
        }
    }

    Board = list->GetListAs2dArray(5);
    Board[2][2]->Toggle();

    while (true)
    {
        if (Engine->Graphics->IsTimeForFrame())
        {
            if (Engine->Mouse->LeftButtonClicked())
            {
                auto pos = Engine->Mouse->GetMousePosition();

                fprintf(stdout, "Click at X: %f, Y: %f \n", pos.X, pos.Y);
            }

            Engine->Play();
        }
    }


    return 0;
}