#include "Stack.h"
#include <string>

template<class T>
T Stack<T>::pop() {
    if(mHead != nullptr) {
        Node* x = mHead;
        mHead = mHead->mNext;
        T retV = x->mValue;
        delete x;
        --mSize;
        return retV;
    }
    throw std::string("Stack is empty");
}

template<class T>
T Stack<T>::top() const {
    if(mHead != nullptr) {
        return mHead->mValue;
    }
    throw std::string("Stack is empty");
}

template<class T>
void Stack<T>::push(T value) {
    Node* x = new Node;
    x->mNext = mHead;
    x->mValue = value;
    mHead = x;
    ++mSize;
}

template<class T>
size_t Stack<T>::size() {
    return mSize;
}

template<class T>
Stack<T>::~Stack() {
    while(mHead != nullptr) {
        Node* x = mHead;
        mHead = mHead->mNext;
        delete x;
    }
}
