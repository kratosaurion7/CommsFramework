#pragma once

#include "PointerList.h"
#include "Pair.h"
#include "RandomGen.h"

class WeightedNumberGenerator
{
public:
    WeightedNumberGenerator();
    ~WeightedNumberGenerator();

    void AddBucket(int bucketNumber, float probability);

    int GetNext();
private:
    PointerList<Pair<int, float>*>* NumberProbabilities;
    RandomGen* _rng;
};

