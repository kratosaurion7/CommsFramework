#pragma once

/** Random generator of selected numbers. Each number has a set percentage of being taken.
 *
 * USAGE :
 *  The generator needs to be filled with numbers with probabilities summing to 1.0 by calling AddBucket
 *  If the total does not sum to 1, the last entry will gain the remainder of the percentage.
 * DEPENDS :
 *  RandomGen
 *  PointerList
 * SPECS :

*/

class RandomGen;

#include "Collections/PointerList.h"
#include "Types/Pair.h"

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

    bool TotalEqualsOne();
};

