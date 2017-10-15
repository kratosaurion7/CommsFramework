#pragma once

#include <queue>
#include <functional>
#include <algorithm>

#include "BaseList.h"

template <class T>
class BaseQueue
{
public:
    BaseQueue()
    {
        innerList = new BaseList<T>();
    };

    ~BaseQueue()
    {
        delete(innerList);
    };

    void Push(T item)
    {
        std::list<T>* x = innerList->GetContainer();

        x->push_back(item);

    };

    T Pop()
    {
        std::list<T>* x = innerList->GetContainer();

        T result = x->front();

        x->pop_front();

        return result;
    };

    T Peek()
    {
        std::list<T>* x = innerList->GetContainer();

        T result = x->front();

        return result;
    };

    //bool BaseStack::HasNext()
    //{
    //    return innerList->Count() > 0;
    //}

    //void BaseQueue::Shuffle()
    //{
    //    innerList->Shuffle();
    //};
    
    void Clear()
    {
        innerList->Clear();
    };

    uint64_t Count()
    {
        return innerList->Count();
    };

    std::list<T>* GetContainer()
    {
        return innerList->GetContainer();
    };

private:
    BaseList<T>* innerList;
};

