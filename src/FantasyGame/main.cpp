
#include "ProgDef.h"

#include <GameEngine.h>
#include <BaseGraphicEngine.h>

#include <BaseSprite.h>
#include <BaseTexture.h>
#include <PointerList.h>
#include <Spritesheet.h>
#include <XFile.h>
#include <XDirectory.h>

#include "MapGrid.h"
#include "Tile.h"

// test comment
int main()
{
    XFile f = XFile("C:\\temp\\Document.txt");
    f.Open();

    exit;

    GameEngine* eng = new GameEngine();

    eng->Init(SCALE_MULTIPLIER * GRID_WIDTH, SCALE_MULTIPLIER * GRID_HEIGHT);

    Spritesheet* sp = new Spritesheet("assets//spritesheet.xml", eng->Graphics);

    eng->Graphics->AddSpritesheet(sp);

    MapGrid* grid = new MapGrid();
    grid->Setup(GRID_HEIGHT, GRID_WIDTH);

    eng->AttachActor(grid);

    while (true)
    {
        eng->Play();

    }

    return 0;
}