
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

// Test includes
#include <PackageFile.h>
#include <EncryptedPackageFile.h>

#define OUT_DIR "C:\\temp\\out.pak"

int main()
{
	char* key = "abcde";
	int len = strlen(key);


	EncryptedPackageFile enc = EncryptedPackageFile(OUT_DIR, key);
	enc.Extract("C:\\temp\\out");

	return 0;

    //PackageFile open = PackageFile(OUT_DIR);
    //open.Extract("C:\\temp\\res");

    //return 0;

    PackageFile pak = PackageFile();
    //pak.AddDirectory("C:\\temp\\depends");
	pak.AddFile("C:\\temp\\text.txt");


    pak.SaveEncrypt(OUT_DIR, key);

    return 0;

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