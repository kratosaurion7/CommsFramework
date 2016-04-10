#include <GameEngine.h>
#include <BaseGraphicEngine.h>

#include <BaseSprite.h>
#include <BaseTexture.h>
#include <PointerList.h>
#include <Spritesheet.h>

#include "MapGrid.h"
#include "Tile.h"

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init(640, 640);

    Spritesheet* sp = new Spritesheet("assets//spritesheet.png", "assets//spritesheet.xml", eng->Graphics);

    eng->Graphics->AddSpritesheet(sp);

    MapGrid* grid = new MapGrid();
    grid->Setup(10, 10);

    eng->AttachActor(grid);

    while (true)
    {
        eng->Play();

    }

    return 0;
}