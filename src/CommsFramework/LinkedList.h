#pragma once

class ListNode
{
public:
    void* Data;
    ListNode* Next;
    
    ListNode();
    ListNode(void* data);
    ~ListNode();
};

class LinkedList
{
private:
    ListNode* FirstNode;
    
public:
    LinkedList();
    ~LinkedList();
    
    void Add(void* data);
    
    void Insert(void* data, int index);
    
    void Remove(int index);
    
    void Delete(int index);
    
    int Count();

private:
    ListNode* GetLastNode();
};