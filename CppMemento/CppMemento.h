#ifndef __CPPMEMENTO_H__
#define __CPPMEMENTO_H__
#pragma once

#include <vector>
#include <map>
#include <string>

class CppMemento {
public:
    CppMemento();
    void load();
    void save();
    void dumpStorage();
    void shuffleByGroup();
    std::string getStringsAtCursor();

private:

    void shuffle( std::vector<std::string>& v);
    
    const std::map<std::string, std::vector<std::string>> mInitialStorage;
    std::map<std::string, std::vector<std::string>> mStorage;
    std::vector<std::string> mCursorPositions;
};

#endif // __CPPMEMENTO_H__
