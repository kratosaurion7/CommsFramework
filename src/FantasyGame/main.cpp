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

class Game_Start_Params;

int main()
{
    int seqLen = 100;
    float* seq = CreateSinusTrack(seqLen, 10);

    TgaFile image = TgaFile();
    image.Init(seqLen, seqLen);
    
    for (int i = 0; i < seqLen; i++)
    {
        int pt = seq[i];
        int baseLine = i + (seqLen * seqLen / 2);
        TgaPix* px = image.Pixels[baseLine + pt];
        px->a = 255;
        px->r = 255;
        px->g = 0;
        px->b = 255;
    }

    image.Save("out.tga");

    return 0;

    FantasyGame* game = new FantasyGame();
    game->ReadConfig();

    game->Init();
    
    game->Start();
    
    game->Play();

    return 0;
}