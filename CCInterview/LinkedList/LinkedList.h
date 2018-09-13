#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#pragma once

#include <iostream>
#include <algorithm>

class LinkedList {
public:
    struct Node {
        Node() : mNext(nullptr){}
        Node* mNext;
        int   mValue;
    };
    
    LinkedList();
    void add(int value);
    void insert(size_t index, int value);
    void replace(size_t index, int value);
    void remove(size_t index);
    int operator[](size_t index) const;
    size_t size() const { return mSize; }
    void partition(int value);
    
    LinkedList& operator<<(int value) { add(value); return *this; }

protected:
    Node* mHead;
    size_t mSize;
};

#endif // __LINKED_LIST_H__