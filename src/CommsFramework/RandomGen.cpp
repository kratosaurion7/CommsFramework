#include "RandomGen.h"



RandomGen::RandomGen(int seed)
{
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
    return (rand() % 100) / 100.0;
}
