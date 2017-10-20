#pragma once

template <class T, class Y>
class Pair
{
public:
    Pair()
    {
    };

    Pair(T item1, Y item2)
    {
        this->Item1 = item1;
        this->Item2 = item2;
    }

    ~Pair()
    {
    };

    T Item1;
    Y Item2;
};

