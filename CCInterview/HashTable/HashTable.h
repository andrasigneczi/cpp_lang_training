#ifndef __HASHTABLE__H
#define __HASHTABLE__H
#pragma once

#include <string>
#include <array>

#define mStorageSize 1000

class HashTable {
public:

    struct Item {
        Item():mNext(0) {}
        Item(std::string key) : mNext(0), mKey(key) {}
        
        Item* mNext;
        const std::string mKey;
        std::string mValue;
    };
    
    HashTable();
    ~HashTable();
    std::string& operator[](const std::string key);
    bool find(const std::string key) const;
    bool remove(const std::string key);
    int keyCount() const {return mKeyCount; }
    
private:
    int hash(std::string key) const;
    
    std::array<Item*,mStorageSize> mStorage;
    int mKeyCount;
};

#endif
