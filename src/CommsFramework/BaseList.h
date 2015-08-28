#pragma once

#include <list>

#include <functional>

#include <algorithm>

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

    void BaseList::Add(T item)
    {
        _container->push_back(item);
    };

    void BaseList::AddRange(BaseList<T>* items)
    {
        auto it = items->GetContainer()->begin();

        while (it != items->GetContainer()->end())
        {
            T listItem = *it;

            _container->push_back(listItem);

            it++;
        }
    };

    T BaseList::Get(int index)
    {
        int i = 0;

        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            if (index == i)
            {
                return *it;
            }

            i++;
        }

        return NULL;
    };

    BaseList<T>* BaseList::Where(std::function<bool(T)> predicate)
    {
        BaseList<T>* retList = new BaseList<T>();

        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            auto test = predicate(*it);

            if (test)
            {
                retList->Add(*it);
            }
        }

        return retList;
    };

    T BaseList::Single(std::function<bool(T)> predicate)
    {
        T retValue = NULL;

        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
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

    void BaseList::ForEach(std::function<void(T)> func)
    {
        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T val = *it;

            func(val);
        }
    }

    int BaseList::IndexOf(T item)
    {
        int i = 0;

        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T current = (*it);

            if (current == item)
            {
                return i;
            }

            i++;
        }

        return NULL;
    };

    void BaseList::RemoveAt(int index)
    {
        _container->erase(index);
    };

    void BaseList::RemoveObject(T object)
    {
        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T current = (*it);

            if (current == object)
            {
                _container->erase(it);
            }
        }
    };

    void Clear()
    {
        _container->clear();
    };

    int BaseList::Count()
    {
        return _container->size();
    };

    std::list<T>* GetContainer() // Temp function to give outsiders a possibility to iterate on the container
    {
        return _container;
    };


protected:
    std::list<T> *_container;
};

template <class T, class U>
BaseList<U>* ListSelect(BaseList<T>* input, std::function<U(T)> selector)
{
    BaseList<U>* outList = new BaseList<U>();

    for (std::list<T>::iterator it = input->GetContainer()->begin(); it != input->GetContainer()->end(); it++)
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

    for (std::list<T>::iterator it = input->GetContainer()->begin(); it != input->GetContainer()->end(); it++)
    {
        T element = *it;

        aggregateValue = func(aggregateValue, element);
    }

    return aggregateValue;
}