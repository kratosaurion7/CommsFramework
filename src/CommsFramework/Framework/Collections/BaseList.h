#pragma once

#include <list>
#include <functional>
#include <algorithm>
#include <cassert>

#include "Math/RandomGen.h"

#define ITBEGIN(x) x->GetContainer()->begin()
#define ITEND(x) x->GetContainer()->end()

template <class T>
class BaseList
{
public:
    BaseList()
    {
        _container = new std::list<T>();
    };

    ~BaseList()
    {
        _container->clear();
        delete(_container);
    };

    void Add(T item)
    {
        _container->push_back(item);
    };

    void AddRange(BaseList<T>* items)
    {
        auto it = items->GetContainer()->begin();

        while (it != items->GetContainer()->end())
        {
            T listItem = *it;

            _container->push_back(listItem);

            it++;
        }
    };

    T Get(int index)
    {
        int i = 0;

        for (typename std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            if (index == i)
            {
                return *it;
            }
            
            i++;
        }

        return NULL;
    };

    T GetBy(std::function<bool(T)> predicate)
    {
        for (typename std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T element = *it;
            
            if (predicate(element))
            {
                return element;
            }
        }

        return NULL;
    };

    T First()
    {
        auto it = _container->begin();

        return (*it);
    };

    T Last()
    {
        auto it = _container->end();

        it--;

        return (*it);
    };

    BaseList<T>* Where(std::function<bool(T)> predicate)
    {
        BaseList<T>* retList = new BaseList<T>();

        for (typename std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            auto test = predicate(*it);

            if (test)
            {
                retList->Add(*it);
            }
        }

        return retList;
    };

    T Single(std::function<bool(T)> predicate)
    {
        T retValue = NULL;

        for (typename std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T val = *it;

            auto test = predicate(*it);

            if (test)
            {
                retValue = val;
            }
        }

        return retValue;
    };

    bool Contains(std::function<bool(T)> predicate)
    {
        for (typename std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T element = *it;

            if (predicate(element))
            {
                return true;
            }
        }

        return false;
    };

    bool ContainsItem(T item)
    {
        for (typename std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T element = *it;

            if (element == item)
            {
                return true;
            }
        }

        return false;
    }

    void ForEach(std::function<void(T)> func)
    {
        for (typename std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T val = *it;

            func(val);
        }
    };

    int IndexOf(T item)
    {
        int i = 0;

        for (typename std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T current = (*it);

            if (current == item)
            {
                return i;
            }
        }

        return NULL;
    };

    void Swap(int indexA, int indexB)
    {
        auto x = _container->begin();
        auto y = _container->begin();
        // I would like to know what type to put in instead of auto
        auto elementA = std::next(x, indexA);
        auto elementB = std::next(y, indexB);

        std::iter_swap(elementA, elementB);
    };

    void Shuffle()
    {
        int length = (int)this->Count();
        RandomGen rng;

        for (int i = length - 1; i > 0; i--)
        {
            int randomIndex = rng.GetRandom(length-1);

            this->Swap(length -1, randomIndex);
        }
    };


    void RemoveAt(int index)
    {
        auto it = _container->begin();

        std::advance(it, index);

        _container->erase(it);
    };

    void RemoveObject(T object)
    {
        for (typename std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T current = (*it);

            if (current == object)
            {
                _container->erase(it);

                break;
            }
        }
    };

    void Clear()
    {
        _container->clear();
    };

    uint64_t Count()
    {
        return _container->size();
    };

    T** GetListAs2dArray(int width)
    {
        assert(width > 0);

        uint64_t totalItems = this->Count();

        if (totalItems % width != 0)
            return NULL;

        int columnIndex = 0;
        int rowIndex = 0;

        T** resultList = new T*[totalItems];
        T* row = new T[width];
        resultList[rowIndex] = row;

        auto it = this->GetContainer()->begin();
        while (it != this->GetContainer()->end())
        {
            resultList[rowIndex][columnIndex] = (*it);

            columnIndex++;

            if (columnIndex % width == 0)
            {
                rowIndex++;
                T* newRow = new T[width];
                resultList[rowIndex] = newRow;

                columnIndex = 0;
            }

            it++;
        }

        return resultList;
    };

    std::list<T>* GetContainer()
    {
        return _container;
    };


protected:
    std::list<T>* _container;

private:
    // Explanation of the neccesary 'typename' keyword : http://pages.cs.wisc.edu/~driscoll/typename.html
    typename std::list<T>::iterator* GetIterator(int index)
    {
        typename std::list<T>::iterator* current = _container->begin();

        for (int i = 0; i < _container->size(); i++)
        {
            if (i == index)
                return current;

            current++;
        }
    };

};

template <class T, class U>
BaseList<U>* ListSelect(BaseList<T>* input, std::function<U(T)> selector)
{
    BaseList<U>* outList = new BaseList<U>();

    for (typename std::list<T>::iterator it = input->GetContainer()->begin(); it != input->GetContainer()->end(); it++)
    {
        auto projected = selector(*it);

        outList->Add(projected);
    }

    return outList;
};

template <class T, class Agg>
Agg ListAggregate(BaseList<T>* input, Agg initial, std::function<Agg(Agg, T)> func)
{
    Agg aggregateValue = initial;

    for (typename std::list<T>::iterator it = input->GetContainer()->begin(); it != input->GetContainer()->end(); it++)
    {
        T element = *it;

        aggregateValue = func(aggregateValue, element);
    }

    return aggregateValue;
}