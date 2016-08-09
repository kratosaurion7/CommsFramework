#define NB_TILES_W 5
#define NB_TILES_H 5


#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <PointerList.h>

#include "GameButton.h"

#define TILE_TOTAL_W TILE_W * TILE_SCALE
#define TILE_TOTAL_H TILE_H * TILE_SCALE

int main()
{
	GameEngine* Engine = new GameEngine();
	Engine->Init(NB_TILES_W * TILE_W * TILE_SCALE, NB_TILES_H * TILE_H * TILE_SCALE);

	list = new PointerList<GameButton*>();

	int index = 0;
	Arr = new GameButton**[NB_TILES_H];
	for (int i = 0; i < NB_TILES_H; i++)
	{
		Arr[i] = new GameButton*[NB_TILES_W];
		for (int j = 0; j < NB_TILES_W; j++)
		{
			GameButton* newBut = new GameButton();
			newBut->TileSprite->SetPos((int)(j * TILE_TOTAL_W), (int)(i * TILE_TOTAL_H));
			newBut->Index = index;
			newBut->PosX = j;
			newBut->PosY = i;

			list->Add(newBut);

			Arr[i][j] = newBut;

			Engine->AttachActor(newBut);

			index++;
		}
	}

	list->Get(12)->ButtonIsOn = true;

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