#include "LinkedList.h"

#include <cstdio>

ListNode::ListNode()
{
    Data = NULL;
    Next = NULL;
}

ListNode::ListNode(void* data)
{
    Data = data;
    Next = NULL;
}

ListNode::~ListNode()
{
    
}

LinkedList::LinkedList()
{
    this->FirstNode = NULL;
};

LinkedList::~LinkedList()
{
    
};

void LinkedList::Add(void* data)
{
    if(this->FirstNode == NULL)
    {
        this->FirstNode = new ListNode(data);
    }
    else
    {
        ListNode* nextNode = this->GetLastNode();
        
        nextNode->Next = new ListNode(data);
    }
};
    
void LinkedList::Insert(void* data, int index)
{
    if (this->FirstNode == NULL)
    {
        this->FirstNode = new ListNode(data);
        
        return;
    }

    int currentIndex = 0;
    ListNode* next = this->FirstNode;

    while (currentIndex < index)
    {
        if (next->Next != NULL)
        {
            next = next->Next;
        }
        else
        {
            // Index is bigger than collection's size. Insert at current position (or throw ?)
            next->Next = new ListNode(data);

            return;
        }

        currentIndex++;
    }

    ListNode* newNode = new ListNode(data);
    newNode->Next = next->Next;

    next->Next = newNode;
    
};
    
void LinkedList::Remove(int index)
{
    if (this->FirstNode == NULL)
        return;

    int currentIndex = 0;
    ListNode* next = this->FirstNode;

    while (currentIndex < index - 1)
    {
        if (next->Next != NULL)
        {
            next = next->Next;
        }
        else
        {
            return;
        }

        currentIndex++;
    }

    ListNode* deleteNode = next->Next;
    if (deleteNode->Next != NULL)
    {
        ListNode* newNextNode = deleteNode->Next;

        next->Next = newNextNode;
    }

    delete(deleteNode);
};

void LinkedList::Delete(int index)
{
    if (this->FirstNode == NULL)
        return;

    int currentIndex = 0;
    ListNode* next = this->FirstNode;

    while (currentIndex < index - 1)
    {
        if (next->Next != NULL)
        {
            next = next->Next;
        }
        else
        {
            return;
        }

        currentIndex++;
    }

    ListNode* deleteNode = next->Next;
    if (deleteNode->Next != NULL)
    {
        ListNode* newNextNode = deleteNode->Next;

        next->Next = newNextNode;
    }

    delete(deleteNode->Next);
    delete(deleteNode);
};

int LinkedList::Count()
{
    int count = 0;
    
    ListNode* next = this->FirstNode;
    while(next != NULL)
    {
        count++;
        next = next->Next;
    }
    
    return count;
};

ListNode* LinkedList::GetLastNode()
{
    ListNode* next = this->FirstNode;
    
    while(next != NULL)
    {
        if(next->Next == NULL)
        {
            return next;
        }
        else
        {
            next = next->Next;
        }
    }
    
    return next;
}