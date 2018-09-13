#include "LinkedList.h"

LinkedList::LinkedList()
: mHead(0)
, mSize(0) {
    
}

void LinkedList::add(int value) {
    ++mSize;
    if(mHead == nullptr) {
        mHead = new Node;
        mHead->mValue = value;
        return;
    }
    
    Node* x = mHead;
    while(x->mNext != nullptr) {
        x = x->mNext;
    }
    x->mNext = new Node;
    x->mNext->mValue = value;
}

void LinkedList::insert(size_t index, int value) {
    if(index > mSize)
        throw "linked list index out of bound exception";
    
    if(index == mSize) {
        add(value);
        return;
    }
    
    ++mSize;
    Node* x = mHead;
    if(index == 0) {
        mHead = new Node;
        mHead->mValue = value;
        mHead->mNext = x;
    } else {
        for(size_t i = 2; i <= index; ++i) {
            x = x->mNext;
        }
        Node* n = new Node;
        n->mValue = value;
        n->mNext = x->mNext;
        x->mNext = n;
    }
}

void LinkedList::replace(size_t index, int value) {
    if(index >= mSize)
        throw "linked list index out of bound exception";
    Node* x = mHead;
    for(size_t i = 1; i <= index; ++i) {
        x = x->mNext;
    }
    x->mValue = value;
}

void LinkedList::remove(size_t index) {
    if(index >= mSize)
        throw "linked list index out of bound exception";
    --mSize;
    Node* x = mHead;
    if(index == 0) {
        mHead = mHead->mNext;
        delete x;
    } else {
        Node* p = nullptr;
        for(size_t i = 1; i <= index; ++i) {
            p = x;
            x = x->mNext;
        }
        p->mNext = x->mNext;
        delete x;
    }
}

int LinkedList::operator[](size_t index) const {
    if(index >= mSize)
        throw "linked list index out of bound exception";
    Node* x = mHead;
    for(size_t i = 1; i <= index; ++i) {
        x = x->mNext;
    }
    return x->mValue;
}

void LinkedList::partition(int value) {
    Node* left   = nullptr;
    Node* right  = nullptr;
    Node* middle = nullptr;
    while(mHead != nullptr) {
        Node* x = mHead;
        if(mHead->mValue < value) {
            mHead = mHead->mNext;
            x->mNext = left;
            left = x;
        } else if(mHead->mValue > value) {
            mHead = mHead->mNext;
            x->mNext = right;
            right = x;
        } else {
            mHead = mHead->mNext;
            x->mNext = middle;
            middle = x;
        }
    }
    
    if( left != nullptr ) {
        mHead = left;
        while(left->mNext != nullptr) {
            left = left->mNext;
        }
        left->mNext = middle;
        while(left->mNext != nullptr) {
            left = left->mNext;
        }
        left->mNext = right;
    } else if( middle != nullptr ) {
        mHead = middle;
        while(middle->mNext != nullptr) {
            middle = middle->mNext;
        }
        middle->mNext = right;
    } else {
        mHead = right;
    }
}
