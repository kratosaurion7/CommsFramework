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
    auto b = new TgaFile();
    b->Init(300, 300);
    b->FillColor(0, 0, 255, 255);

    auto g = new TgaFile();
    g->Init(300, 300);
    g->FillColor(0, 255, 0, 255);

    auto r = new TgaFile();
    r->Init(300, 300);
    r->FillColor(255, 0, 0, 255);


    FantasyGame* game = new FantasyGame();
    game->ReadConfig();

    game->Init();
    
    game->Start();
    
    game->Play();

    return 0;
}