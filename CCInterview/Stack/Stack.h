#ifndef __STACK_H__
#define __STACK_H__
#pragma once

#include <cstddef>

template<class T>
class Stack {
public:
    struct Node {
        Node() : mNext(nullptr), mValue(0) {}
        Node* mNext;
        T     mValue;
    };
    
    Stack() : mSize(0), mHead(nullptr) {}
    ~Stack();
    T pop();
    T top() const;
    void push(T value);
    size_t size();
    
    Stack<T>& operator<<(T value) { push(value); return *this; }
    
private:
    size_t mSize;
    Node*  mHead;
};

#include "Stack.cpp"

#endif // __STACK_H__