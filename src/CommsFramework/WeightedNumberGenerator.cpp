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

    NumberProbabilities->GetContainer()->sort([](Pair<int, float>* a, Pair<int, float>* b) {
        return b->Item2 > a->Item2;
    });
}

int WeightedNumberGenerator::GetNext()
{
    bool test = TotalEqualsOne();

    float percentage = _rng->GetRandomPercentage();

    for (int i = 0; i < NumberProbabilities->Count(); i++)
    {
        Pair<int, float>* bucket = NumberProbabilities->Get(i);

        if (percentage < bucket->Item2)
            return bucket->Item1;
    }

    return NumberProbabilities->Get(NumberProbabilities->Count() - 1)->Item1;
}

bool WeightedNumberGenerator::TotalEqualsOne()
{
    float total = 0;

    auto it = NumberProbabilities->GetContainer()->begin();
    while (it != NumberProbabilities->GetContainer()->end())
    {
        Pair<int, float>* pair = (*it);
        total += pair->Item2;

        it++;
    }

    return total == 1.0;
}
