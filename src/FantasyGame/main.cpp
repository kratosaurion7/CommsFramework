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

int main()
{
    ConfigurationManager man = ConfigurationManager();
    man.LoadConfig();

    auto res = man.FindValue<int>("window_width")->As<long>()->WithDefault(445)->Get();

    FantasyGame* game = new FantasyGame();

    game->Init();
    
    game->Start();
    
    game->Play();

    return 0;
}

