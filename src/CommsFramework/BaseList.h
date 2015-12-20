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

    T BaseList::GetBy(std::function<bool(T)> predicate)
    {
        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T element = *it;
            
            if (predicate(element))
            {
                return element;
            }
        }

        return NULL;
    };

    T BaseList::First()
    {
        auto it = _container->begin();

        return (*it);
    };

    T BaseList::Last()
    {
        auto it = _container->end();

        it--;

        return (*it);
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

    bool BaseList::Contains(std::function<bool(T)> predicate)
    {
        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T element = *it;

            if (predicate(element))
            {
                return true;
            }
        }

        return false;
    };

    bool BaseList::ContainsItem(T item)
    {
        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T element = *it;

            if (element == item)
            {
                return true;
            }
        }

        return false;
    }

    void BaseList::ForEach(std::function<void(T)> func)
    {
        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            T val = *it;

            func(val);
        }
    };

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
        }

        return NULL;
    };

    void BaseList::Swap(int indexA, int indexB)
    {
        auto x = _container->begin();
        auto y = _container->begin();
        // I would like to know what type to put in instead of auto
        auto elementA = std::next(x, indexA);
        auto elementB = std::next(y, indexB);

        std::iter_swap(elementA, elementB);
    };

    void BaseList::Shuffle()
    {
        int length = this->Count();
        RandomGen rng;

        for (int i = length - 1; i > 0; i--)
        {
            int randomIndex = rng.GetRandom(length-1);

            this->Swap(length -1, randomIndex);
        }
    };


    void BaseList::RemoveAt(int index)
    {
        auto it = _container->begin();

        std::advance(it, index);

        _container->erase(it);
    };

    void BaseList::RemoveObject(T object)
    {
        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
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

    int BaseList::Count()
    {
        return _container->size();
    };

    std::list<T>* GetContainer() // Temp function to give outsiders a possibility to iterate on the container
    {
        return _container;
    };


protected:
    std::list<T>* _container;

private:
    // Explanation of the neccesary 'typename' keyword : http://pages.cs.wisc.edu/~driscoll/typename.html
    typename std::list<T>::iterator* GetIterator(int index)
    {
        std::list<T>::iterator* current = _container->begin();

        for (int i = 0; i < _container->size; i++)
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