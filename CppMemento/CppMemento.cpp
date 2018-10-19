#include "CppMemento.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>


void CppMemento::shuffle( std::vector<std::string>& v)
{
    //std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(v.begin(), v.end(), g);
 
    //std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "; "));
    //std::cout << "\n";
}




std::string CppMemento::trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r\a");
    if (std::string::npos == first) {
        if(str.length() == 0)
            return "";
        switch(str[0]) {
            case ' ': case '\t': case '\n': case '\r': case '\a': return "";
            break;
            default:
            break;
        }
        return str;
    }

    size_t last = str.find_last_not_of(" \t\n\r\a");
    return str.substr(first, (last - first + 1));
}

CppMemento::CppMemento()
: mInitialStorage {{"a", {"b", "c"}},
    {"d", {"e", "f", "g"}},} {
        
   // mStorage.emplace( "sss", std::initializer_list<std::string>{"ee", "bb"} );
}

void CppMemento::Init() {
    std::ifstream file( "questionlist.txt", std::ios::in );
    std::string line;
    std::vector<std::string> lines;
    std::string groupName;
    while( !file.eof()) {
            getline( file, line );
            
            if(line[0] == ' ' || line[0] == '\t' || line[0] == '\n' || line[0] == '\r' || line[0] == '\a') {
                // we have a topic
                line = trim(line);
                if(line.length() > 0) {
                    lines.push_back(line);
                } else {
                    if(groupName.length() > 0 && lines.size() > 0) {
                        mStorage.emplace( groupName, lines );
                    }
                    groupName = "";
                    lines.clear();
                }
            } else {
                // we have a groupName
                if(groupName.length() > 0 && lines.size() > 0) {
                    mStorage.emplace( groupName, lines );
                }
                groupName = trim(line);
                lines.clear();
            }
    }
    if(groupName.length() > 0 && lines.size() > 0) {
        mStorage.emplace( groupName, lines );
    }
    std::cout << "read line count: " << lines.size() << std::endl;
    for( auto it = mStorage.begin(); it != mStorage.end(); ++it) {
        shuffle(it->second);
    }    
}

void CppMemento::dumpStorage() {
    for( auto it = mStorage.begin(); it != mStorage.end(); ++it) {
        std::cout << "+ " << it->first << "\n";
        for( auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            std::cout << " \\" << std::string(2,'-') << ' ' << *it2 << "\n";
        }
    }
}