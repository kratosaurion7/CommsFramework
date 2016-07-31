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
    int amplitude = 20;
    int height = amplitude * 2;
    int seqLen = 100;
    int smoothFactor = 20;
    int curveLen = seqLen * smoothFactor;

    float* seq = CreateSinusTrack(seqLen, amplitude);
    float* smoothedSeq = SmoothCurveTrack(seq, seqLen, smoothFactor);

    TgaFile image = TgaFile();
    image.Init(curveLen, height);
    
    for (int i = 0; i < curveLen; i++)
    {
        int pt = smoothedSeq[i];
        int baseLine = i + (curveLen * height / 2);

        int pixAddress = baseLine + (pt * seqLen);
        TgaPix* px = image.Get(i, (height / 2) + pt);
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