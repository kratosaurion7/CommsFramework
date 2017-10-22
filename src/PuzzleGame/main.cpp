#include <Engine/GameEngine.h>
#include <Graphic/Base Classes/BaseGraphicEngine.h>

#include "GameCore.h"
#include "GameButton.h"

#include <stdio.h>

GameEngine* Engine;

void play_one();

#ifdef __EMSCRIPTEN__

#include <emscripten.h>

#endif

#ifdef WIN32
#include "Graphic/DX2D/DX2DGraphicEngine.h"
#endif
int main()
{

//#ifdef WIN32
//    DX2DGraphicEngine* eng = new DX2DGraphicEngine();
//
//    GraphicEngineInitParams params;
//    params.EnableVerticalSync = true;
//    params.WindowSize = new FSize(600, 600);
//    params.WindowTitle = "TITEL";
//    
//    eng->Initialize(&params);
//
//    while(true)
//    {
//        eng->ProcessEvents();
//    }
//
//    return 0;
//#endif

    Engine = new GameEngine();
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

#ifdef __EMSCRIPTEN__

    emscripten_set_main_loop(play_one, 30, 0);

#else
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
#endif

    return 0;
}

void play_one()
{
    printf("Rendering\n");

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