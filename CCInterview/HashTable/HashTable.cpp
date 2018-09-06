#include "HashTable.h"
#include <algorithm>

HashTable::HashTable()
: mStorage{}
, mKeyCount(0) {
    
}

HashTable::~HashTable() {
    std::for_each(mStorage.begin(), mStorage.end(), [](Item*x){
        while( x != nullptr ) {
            Item* n = x->mNext;
            delete x;
            x = n;
        }
    });
}

std::string& HashTable::operator[](const std::string key) {
    int index = hash(key) % mStorageSize;
    Item* retP = nullptr;
    if( mStorage[index] == nullptr ) {
        retP = new Item(key);
        mStorage[index] = retP;
        ++mKeyCount;
    } else {
        retP = mStorage[index];
        while( retP != nullptr && retP->mKey != key ) {
            retP = retP->mNext;
        }
        if( retP == nullptr ) {
            retP = new Item(key);
            retP->mNext = mStorage[index];
            mStorage[index] = retP;
            ++mKeyCount;
        }
    }
    return retP->mValue;
}

int HashTable::hash(const std::string key) {
    int hkey = 0;
    std::for_each(key.begin(),key.end(),[&hkey](const char&x){ hkey += x; });
    return hkey;
}

bool HashTable::find(const std::string key) {
    int index = hash(key) % mStorageSize;
    if( mStorage[index] == nullptr )
        return false;
    
    Item* x = mStorage[index];
    while( x != nullptr && x->mKey != key ) {
        x = x->mNext;
    }
    return x != nullptr;
}

bool HashTable::remove(const std::string key) {
    bool retVal = false;
    int index = hash(key) % mStorageSize;
    
    if( mStorage[index] == nullptr )
        return retVal;
    
    Item* x = mStorage[index];
    Item* p = nullptr;
    while( x != nullptr ) {
        if( x->mKey == key ) {
            if( x == mStorage[index] ) {
                mStorage[index] = mStorage[index]->mNext;
                delete x;
                retVal = true;
                break;
            } else {
                p->mNext = x->mNext;
                delete x;
                retVal = true;
                break;
            }
        }
        p = x;
        x = x->mNext;
    }
    
    if( retVal )
        --mKeyCount;
    return retVal;
}
