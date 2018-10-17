#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <cstddef>

class EmptyQueueException;

template<class T>
class Queue {
    struct Node {
        Node* mNext;
        T mValue;
    };

public:
    Queue() : mFirst(nullptr), mLast(nullptr), mSize(0) {}
    ~Queue();
    void add(T value);
    T get();
    size_t size() const { return mSize; }
    Queue<T>& operator<<(T value) { add(value); return *this; }
    
private:
    Node*  mFirst;
    Node*  mLast;
    size_t mSize;
};

#include "Queue.cpp"

#endif // __QUEUE_H__