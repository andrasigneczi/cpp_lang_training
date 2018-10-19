#ifndef __CPPMEMENTO__
#define __CPPMEMENTO__
#pragma once

#include <vector>
#include <map>
#include <string>

class CppMemento {
public:
    CppMemento();
    void Init();
    void dumpStorage();
    
private:
    std::string trim(const std::string& str);
    void shuffle( std::vector<std::string>& v);
    
    const std::map<std::string, std::vector<std::string>> mInitialStorage;
    std::map<std::string, std::vector<std::string>> mStorage;
};

#endif // __CPPMEMENTO__
