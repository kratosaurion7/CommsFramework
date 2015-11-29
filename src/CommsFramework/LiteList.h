#pragma once

#include <functional>
#include <algorithm>

template<class T>
class LiteList;

template<class T>
class LiteListIterator;

template<class T>
class ITEM;

template<class T>
class ITEM
{
public:
    T contents;
    ITEM* next;

    ITEM()
    {
        contents = NULL;
        next = NULL;
    }

    ~ITEM()
    {

    }
};

template<class T>
class LiteListIterator
{
public:
    LiteListIterator(ITEM<T>* targetList)
    {
        currentItem = targetList;
    };

    ~LiteListIterator()
    {

    };

    T GetNext()
    {
        if (currentItem == NULL)
            return NULL;

        T nextItem = currentItem->contents;

        currentItem = currentItem->next;

        return nextItem;
    };

    bool HasNext()
    {
        if (currentItem == NULL)
            return false;

        return currentItem != NULL;
    }
private:
    ITEM<T>* currentItem;
};


template <class T>
class LiteList
{
public:
    LiteList()
    {
        FirstItem = NULL;
    };

    ~LiteList()
    {

    };

    LiteListIterator<T>* GetIterator()
    {
        LiteListIterator<T>* iter = new LiteListIterator<T>(this->FirstItem);

        return iter;
    };

    void LiteList::Add(T item)
    {
        ITEM<T>* newStruct = new ITEM<T>();
        newStruct->contents = item;
        newStruct->next = NULL;

        this->AddItem(newStruct);
    };

    void LiteList::AddRange(LiteList<T>* items)
    {
        
    };

    T LiteList::Get(int index)
    {
        int current = 0;
        ITEM<T>* currentItem = FirstItem;

        while (current < index)
        {
            currentItem = currentItem->next;
            current++;

            if (currentItem == NULL)
                return NULL;
        }

        return currentItem->contents;
    };

    T LiteList::GetBy(std::function<bool(T)> predicate)
    {
        return 0;
    };

    LiteList<T>* LiteList::Where(std::function<bool(T)> predicate)
    {
        return 0;
    };

    T LiteList::Single(std::function<bool(T)> predicate)
    {
        return 0;
    };

    bool LiteList::Contains(std::function<bool(T)> predicate)
    {
        return false;
    };

    bool LiteList::ContainsItem(T item)
    {
        return false;
    };

    void LiteList::ForEach(std::function<void(T)> func)
    {

    };

    int LiteList::IndexOf(T item)
    {
        return 0;
    };

    void LiteList::Swap(int indexA, int indexB)
    {

    };

    void LiteList::Shuffle()
    {

    };

    void LiteList::RemoveAt(int index)
    {
        int current = 0;

        if (FirstItem == NULL)
            return;

        ITEM<T>* previousItem = NULL;
        ITEM<T>* currentItem = FirstItem;

        while (current < index)
        {
            previousItem = currentItem;
            currentItem = currentItem->next;
            current++;

            if (currentItem == NULL)
                return; // Index bigger than list count           
        }

        if (currentItem->next == NULL)
            return;

        previousItem->next = currentItem->next;

        delete(currentItem);
    };

    void LiteList::RemoveObject(T object)
    {

    };

    void LiteList::Clear()
    {

    };

    int LiteList::Count()
    {
        int amount = 0;
        ITEM<T>* nextItem = FirstItem;

        while (nextItem != NULL)
        {
            amount++;
            nextItem = nextItem->next;
        }

        return amount;
    };

private:
    ITEM<T>* FirstItem;

    void LiteList::AddItem(ITEM<T>* item)
    {
        if (FirstItem == NULL)
        {
            FirstItem = item;
        }
        else
        {
            ITEM<T>* nextItem = FirstItem;

            while (nextItem->next != NULL)
            {
                nextItem = nextItem->next;
            }

            nextItem->next = item;
        }
    };
};