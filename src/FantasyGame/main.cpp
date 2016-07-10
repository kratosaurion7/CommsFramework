
#include "ProgDef.h"

#include <GameEngine.h>
#include <BaseGraphicEngine.h>

#include <BaseSprite.h>
#include <BaseTexture.h>
#include <PointerList.h>
#include <Spritesheet.h>
#include <XFile.h>
#include <XDirectory.h>

#include "LocalGrid.h"

// test comment

// Test includes
#include <PackageFile.h>
#include <EncryptedPackageFile.h>
#include <sstream>

#define OUT_DIR "C:\\temp\\out.pak"

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init(SCALE_MULTIPLIER * GRID_WIDTH, SCALE_MULTIPLIER * GRID_HEIGHT);

    Spritesheet* sp = new Spritesheet("assets//spritesheet.xml", eng->Graphics);

    eng->Graphics->AddSpritesheet(sp);

    LocalGrid* grid = new LocalGrid(NULL);
    grid->Setup(GRID_HEIGHT, GRID_WIDTH);

    eng->AttachActor(grid);

    while (true)
    {
        eng->Play();

    }

    return 0;
}