#pragma once

#include <list>
#include <functional>
#include <algorithm>

#include "Collections/BaseList.h"

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

    void Push(T item)
    {
        std::list<T>* x = innerList->GetContainer();

        x->push_front(item);
    };

    T Pop()
    {
        if (this->Count() > 0)
        {
            std::list<T>* x = innerList->GetContainer();

            T result = x->front();

            x->pop_front();

            return result;
        }

        return NULL;
    };

    T Peek()
    {
        if (this->Count() > 0)
        {
            std::list<T>* x = innerList->GetContainer();

            T result = x->front();

            return result;
        }

        return NULL;
    };

    bool HasNext()
    {
        return innerList->Count() > 0;
    }

    // Stack should probably not have a Shuffle method.
    void Shuffle()
    {
        innerList->Shuffle();
    };

    void Clear()
    {
        innerList->Clear();
    };

    uint64_t Count()
    {
        return innerList->Count();
    };

    void Release()
    {
        //for (std::list<T>::iterator it = innerList->GetContainer()->begin(); it != innerList->GetContainer()->end(); it++)
        //{
        //    delete *it;
        //}

        //innerList->GetContainer()->clear();
    };

    std::list<T>* GetContainer()
    {
        return innerList->GetContainer();
    };

private:
    BaseList<T>* innerList;
};

