
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

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init(SCALE_MULTIPLIER * GRID_WIDTH, SCALE_MULTIPLIER * GRID_HEIGHT);

    Spritesheet* sp = new Spritesheet("assets//spritesheet.xml", eng->Graphics);

    eng->Graphics->AddSpritesheet(sp);

    FantasyGame* game = new FantasyGame();
    eng->AttachActor(game);
    game->Start(NULL);
    

    while (true)
    {
        eng->Play();

    }

    return 0;
}