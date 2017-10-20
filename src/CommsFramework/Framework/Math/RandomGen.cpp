#include "RandomGen.h"
#include "Utilities.h"

RandomGen::RandomGen(int seed)
{
    if (seed == 0)
    {
        srand(GetTicks());
    }
    else
    {
        srand(seed);
    }
}


RandomGen::~RandomGen()
{
}

int RandomGen::GetRandom(int max)
{
    return rand() % max;
}

float RandomGen::GetRandomPercentage()
{
    return (float)((rand() % 100) / 100.0);
}
