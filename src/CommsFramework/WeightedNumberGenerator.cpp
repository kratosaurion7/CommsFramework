#include "WeightedNumberGenerator.h"



WeightedNumberGenerator::WeightedNumberGenerator()
{
    NumberProbabilities = new PointerList<Pair<int, float>*>();
    _rng = new RandomGen();
}


WeightedNumberGenerator::~WeightedNumberGenerator()
{
    NumberProbabilities->Release();
    delete(NumberProbabilities);

    delete(_rng);
}

void WeightedNumberGenerator::AddBucket(int bucketNumber, float probability)
{
    Pair<int, float>* newPair = new Pair<int, float>(bucketNumber, probability);

    NumberProbabilities->Add(newPair);
}

int WeightedNumberGenerator::GetNext()
{
    float percentage = _rng->GetRandomPercentage();

    for (int i = 0; i < NumberProbabilities->Count(); i++)
    {
        Pair<int, float>* bucket = NumberProbabilities->Get(i);

        if (i + 1 == NumberProbabilities->Count())
            return bucket->Item1;
        
        Pair<int, float>* nextBucket = NumberProbabilities->Get(i + 1);

        // If current bucket is between the current percentage and the next one
        if (percentage >= bucket->Item2 && percentage < nextBucket->Item2)
        {
            return bucket->Item1;
        }
    }

    // Not supposed to arrive here.
    return NumberProbabilities->Get(NumberProbabilities->Count())->Item1;
}
