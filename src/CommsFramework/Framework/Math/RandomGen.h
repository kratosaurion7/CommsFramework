#pragma once

/** Random Generator
 * 
 * USAGE : 
 *  Call GetRandom and specify an integer as the maximum to return. The random will be between 0 and MAX-1.
 *  There is also a method to return a random percentage between 0 and 99.
*/

#include <random>

class RandomGen
{
public:
    RandomGen(int seed = 0);
    ~RandomGen();

    int GetRandom(int max = RAND_MAX);

    float GetRandomPercentage();
private:
    
};

