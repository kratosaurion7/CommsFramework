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


#include <ConfigurationManager.h>
#include "SimpleMenu.h"

int main()
{
    


    FantasyGame* game = new FantasyGame();

    SimpleMenu* mnu = new SimpleMenu(game->Engine);


    game->Init();
    
    game->Start();
    
    game->Play();

    return 0;
}

