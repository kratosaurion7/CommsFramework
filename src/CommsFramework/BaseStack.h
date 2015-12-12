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
        //if (innerList->Count() > 0)
        //{
            std::list<T>* x = innerList->GetContainer();

            T result = x->front();

            x->pop_front();

            return result;
        //}

        //return NULL;
    };

    T BaseStack::Peek()
    {
        //if (innerList->Count() > 0)
        //{
            std::list<T>* x = innerList->GetContainer();

            T result = x->front();

            return result;
        //}

        //return NULL;
    };

    //bool BaseStack::HasNext()
    //{
    //    return innerList->Count() > 0;
    //}

    void BaseStack::Shuffle()
    {
        innerList->Shuffle();
    };

    void BaseStack::Clear()
    {
        innerList->Clear();
    };

    int BaseStack::Count()
    {
        return innerList->Count();
    };

    std::list<T>* BaseStack::GetContainer()
    {
        return innerList->GetContainer();
    };

private:
    BaseList<T>* innerList;
};

