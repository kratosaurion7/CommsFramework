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

class Game_Start_Params;

int main()
{
    FantasyGame* game = new FantasyGame();
	Game_Start_Params* params = game->ReadParametersConfig("assets\\game_config.xml");
    game->Start(params);
    
    game->Play();

    return 0;
}