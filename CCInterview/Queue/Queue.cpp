#include "Queue.h"

template<class T>
Queue<T>::~Queue() {
    
}

template<class T>
void Queue<T>::add(T value) {
    if(mFirst == nullptr) {
        mFirst = new Node;
        mLast = mFirst;
        mFirst->mValue = value;
        ++mSize;
        return;
    }
    Node* x = new Node;
    x->mValue = value;
    mLast->mNext = x;
    mLast = x;
    ++mSize;
}

template<class T>
T Queue<T>::get() {
    if(mFirst == nullptr) {
        throw EmptyQueueException();
    }
    T retV = mFirst->mValue;
    Node* x = mFirst;
    mFirst = mFirst->mNext;
    delete x;
    if( mFirst == nullptr) {
        mLast = nullptr;
    }
    --mSize;
    return retV;
}
