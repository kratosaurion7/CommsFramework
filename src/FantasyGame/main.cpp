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
    int seqLen = 100;
    int smoothFactor = 5;
    int curveLen = seqLen * smoothFactor - (smoothFactor);

    float* seq = CreateCosineTrack(seqLen, amplitude);
    float* smoothedSeq = SmoothCurveTrack(seq, seqLen, smoothFactor);

    auto x = PlotSequenceToImage(smoothedSeq, curveLen);
    x->Save("cos.tga");
    return 0;

    FantasyGame* game = new FantasyGame();
    game->ReadConfig();

    game->Init();
    
    game->Start();
    
    game->Play();

    return 0;
}