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
#include "Map.h"

#include <TgaFile.h>
#include <Functions.h>
#include <ImageLoader.h>

#include <Utils.h>


int main()
{
    FantasyGame* game = new FantasyGame();
    game->ReadConfig();

    game->Init();
    
    game->Start();
    
    game->Play();

    return 0;
}

