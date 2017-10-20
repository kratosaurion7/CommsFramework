#pragma once


class MyArrayList
{
private:
    int currentLength; // Total amount of space in the array
    void** arrayElements;

    int elementsCount; // Number of items in the array

public:
    MyArrayList();
    MyArrayList(int initialSize);
    ~MyArrayList();

    void Add(void* data);

    void Insert(void* data, int index);

    void Remove(int index);

    void Delete(int index);

    int Count();

private:
    int FindNextPosition();

    bool HasEnoughRoom(int indexNeeded = 1);

    void Grow(int minimumAmount, float growAmount = 1.33);

    void MoveOut(int startIndex, int moveAmount = 1);

    void MoveIn(int startIndex, int moveAmount = 1);
};