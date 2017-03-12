#include "MyArrayList.h"

#include <string>
#include <math.h>

MyArrayList::MyArrayList()
{
    currentLength = 10;

    arrayElements = new void*[currentLength];
    for (int i = 0; i < currentLength; i++)
    {
        arrayElements[i] = NULL;
    }

    elementsCount = 0;
}

MyArrayList::MyArrayList(int initialSize)
{
    currentLength = initialSize;

    arrayElements = new void*[currentLength];
    for (int i = 0; i < currentLength; i++)
    {
        arrayElements[i] = NULL;
    }
    
    elementsCount = 0;
}


MyArrayList::~MyArrayList()
{
}

void MyArrayList::Add(void* data)
{
    if (HasEnoughRoom() == false)
    {
        Grow(1);
    }

    int nextFreeIndex = this->FindNextPosition();

    arrayElements[nextFreeIndex] = data;

    elementsCount++;
}

void MyArrayList::Insert(void* data, int index)
{
    if (index >= elementsCount)
        return;

    MoveOut(index);
    
    arrayElements[index] = data;
}

void MyArrayList::Remove(int index)
{
    if (index >= elementsCount)
        return;

    arrayElements[index] = NULL;

    MoveIn(index);
}

void MyArrayList::Delete(int index)
{
    if (index >= elementsCount)
        return;

    delete(arrayElements[index]);
    arrayElements[index] = NULL;

    MoveIn(index);
}

int MyArrayList::Count()
{
    return elementsCount;
}

int MyArrayList::FindNextPosition()
{
    return elementsCount;
}

bool MyArrayList::HasEnoughRoom(int amountNeeded)
{
    return elementsCount + amountNeeded < currentLength;
}

void MyArrayList::Grow(int minimumAmount, float growAmount)
{
    int newArrayLength = 0;
    if (currentLength * growAmount > minimumAmount)
    {
        
        newArrayLength = ceil(currentLength * growAmount);
    }
    else
    {
        newArrayLength = ceil((currentLength + minimumAmount) * growAmount);
    }

    auto newArray = new void*[newArrayLength];
    //memcpy(newArray, arrayElements, elementsCount);

    for (int i = 0; i < currentLength; i++)
    {
        newArray[i] = arrayElements[i];
    }
    
    delete(arrayElements);

    arrayElements = newArray;
}

void MyArrayList::MoveOut(int startIndex, int moveAmount)
{
    if (HasEnoughRoom(moveAmount))
    {
        Grow(moveAmount);
    }

    for (int i = elementsCount; i > startIndex; i--)
    {
        arrayElements[i] = arrayElements[i - 1];
    }

    arrayElements[startIndex] = NULL;

    elementsCount += moveAmount;
}

void MyArrayList::MoveIn(int startIndex, int moveAmount)
{
    for (int i = startIndex; i < elementsCount - 1; i++)
    {
        arrayElements[i] = arrayElements[i + 1];
    }

    arrayElements[elementsCount - 1] = NULL;
    elementsCount--;
}
