#ifndef __CPPMEMENTO_H__
#define __CPPMEMENTO_H__
#pragma once

#include <vector>
#include <map>
#include <string>

class CppMemento {
public:
    CppMemento();
    void load(std::string fileName);
    void save(std::string fileName);
    void dumpStorage() const;
    void shuffleByGroup();
    std::string getStringsAtCursor();
    void incCursor() {++mCursorPosition;}
    void decCursor() {--mCursorPosition;}
private:

    void shuffle( std::vector<std::string>& v);
    
    const std::map<std::string, std::vector<std::string>> mInitialStorage;
    std::map<std::string, std::vector<std::string>> mStorage;
    int mCursorPosition;
};

#endif // __CPPMEMENTO_H__
