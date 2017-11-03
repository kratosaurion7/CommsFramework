#include "ProgDef.h"

#include <Engine/GameEngine.h>
#include <Graphic/Base Classes/BaseGraphicEngine.h>

#include <Graphic/Base Classes/BaseSprite.h>
#include <Graphic/Base Classes/BaseTexture.h>
#include <Collections/PointerList.h>
#include <Graphic/Spritesheet/Spritesheet.h>
#include <Filesystem/XFile.h>
#include <Filesystem/XDirectory.h>

#include "FantasyGame.h"
#include "Map.h"

#include <Image/TgaFile.h>
#include <Math/Functions.h>
#include <System/Windows/ImageLoader.h>

#include <Configuration/ConfigurationManager.h>
#include "SimpleMenu.h"

int main()
{
    


    FantasyGame* game = new FantasyGame();



    game->Init();
    
    game->Start();
    
    game->Play();

    return 0;
}

