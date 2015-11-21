#pragma once

#include <list>
#include <functional>
#include <algorithm>

#include "BaseList.h"

template <class T>
class BaseStack
{
public:
    BaseStack()
    {
        innerList = new BaseList<T>();
    };

    ~BaseStack()
    {
        delete(innerList);
    };

    void BaseStack::Push(T item)
    {
        std::list<T>* x = innerList->GetContainer();

        x->push_front(item);
        
    };

    T BaseStack::Pop()
    {
        std::list<T>* x = innerList->GetContainer();
        
        T result = x->front();

        x->pop_front();

        return result;
    };

    T BaseStack::Peek()
    {
        std::list<T>* x = innerList->GetContainer();

        T result = x->front();

        return result;
    };

    void BaseStack::Shuffle()
    {
        innerList->Shuffle();
    };

    void BaseStack::Clear()
    {
        innerList->Clear();
    }

    std::list<T>* BaseStack::GetContainer()
    {
        return innerList->GetContainer();
    };

private:
    BaseList<T>* innerList;
};

