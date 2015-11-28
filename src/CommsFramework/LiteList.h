#pragma once

#include <functional>
#include <algorithm>

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

    void LiteList::Add(T item)
    {
        ITEM* newStruct = new ITEM;
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
        ITEM* currentItem = FirstItem;

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

        ITEM* previousItem = NULL;
        ITEM* currentItem = FirstItem;

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
        ITEM* nextItem = FirstItem;

        while (nextItem != NULL)
        {
            amount++;
            nextItem = nextItem->next;
        }

        return amount;
    };

private:
    struct ITEM
    {
        T contents;
        ITEM* next;
    };

    ITEM* FirstItem;

    void LiteList::AddItem(ITEM* item)
    {
        if (FirstItem == NULL)
        {
            FirstItem = newItem;
        }
        else
        {
            ITEM* nextItem = FirstItem;

            while (nextItem->next != NULL)
            {
                nextItem = nextItem->next;
            }

            nextItem->next = newItem;
        }
    };
};