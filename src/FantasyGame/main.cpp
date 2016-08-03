#include "ProgDef.h"

#include <GameEngine.h>
#include <BaseGraphicEngine.h>

#include <BaseSprite.h>
#include <BaseTexture.h>
#include <PointerList.h>
#include <Spritesheet.h>
#include <XFile.h>
#include <XDirectory.h>

#include "FantasyGame.h"
#include "LocalGrid.h"

#include <TgaFile.h>
#include <Functions.h>
#include <ImageLoader.h>

#include <Utils.h>


class Game_Start_Params;
class IWICBitmap;

int main()
{
    ImageLoader ldr = ImageLoader();

    TgaFile* img = new TgaFile();
    img->Init(256, 256);
    img->FillColor(255, 0, 0, 255);
    img->Save("test.tga");


    auto bits = ldr.CreateBits(img);

    return 0;




    FantasyGame* game = new FantasyGame();
    game->ReadConfig();

    game->Init();
    
    game->Start();
    
    game->Play();

    return 0;
}