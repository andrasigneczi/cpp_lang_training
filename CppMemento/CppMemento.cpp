#include "CppMemento.h"
#include "stringutil.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>

void CppMemento::shuffle( std::vector<std::string>& v)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
}




CppMemento::CppMemento()
: mInitialStorage {{"a", {"b", "c"}},
    {"d", {"e", "f", "g"}},},
mCursorPosition(0) {
   // mStorage.emplace( "sss", std::initializer_list<std::string>{"ee", "bb"} );
}

void CppMemento::load(std::string fileName) {
    std::ifstream file( fileName, std::ios::in );
    std::string line;
    std::vector<std::string> lines;
    std::string groupName;
    while( !file.eof()) {
            getline( file, line );
            
            if(line[0] == ' ' || line[0] == '\t' || line[0] == '\n' || line[0] == '\r' || line[0] == '\a') {
                // we have a topic
                line = StringUtil::trim(line);
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
                // maybe we have a groupName
                if(groupName.length() > 0 && lines.size() > 0) {
                    mStorage.emplace( groupName, lines );
                }
                groupName = StringUtil::trim(line);
                lines.clear();

                if(line.substr(0,7) == "cursor:") {
                    // load the cursor positions
                    mCursorPosition = std::stoi(StringUtil::trim(line.substr(7)));
                }
            }
    }
    if(groupName.length() > 0 && lines.size() > 0) {
        mStorage.emplace( groupName, lines );
    }
}

void CppMemento::shuffleByGroup() {
    // Shuffle by group
    for( auto it = mStorage.begin(); it != mStorage.end(); ++it) {
        shuffle(it->second);
    }
}

void CppMemento::save(std::string fileName) {
    /*
    ios::in	Open for input operations.
    ios::out	Open for output operations.
    ios::binary	Open in binary mode.
    ios::ate	Set the initial position at the end of the file.
    If this flag is not set, the initial position is the beginning of the file.
    ios::app	All output operations are performed at the end of the file, appending the content to the current content of the file.
    ios::trunc	If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one.
    */
    std::ofstream file( fileName, std::ios::out | std::ios::trunc );
    for( auto it = mStorage.begin(); it != mStorage.end(); ++it) {
        file << it->first << std::endl;
        for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            file << std::string(4, ' ') << *it2 << std::endl;
        }
    }

    file << std::endl;
    file << "cursor: " << (mCursorPosition % 1000) << std::endl;
}

void CppMemento::dumpStorage() const {
    for( auto it = mStorage.begin(); it != mStorage.end(); ++it) {
        std::cout << "+ " << it->first << "\n";
        for( auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            std::cout << " \\" << std::string(2,'-') << ' ' << *it2 << "\n";
        }
    }
}

std::string CppMemento::getStringsAtCursor() {
    std::string retVal;
    size_t index = 0;
    for( auto it = mStorage.begin(); it != mStorage.end(); ++it) {
        int pos = mCursorPosition % it->second.size();
        if(index > 0)
            retVal += "\n";
        retVal += "- " + it->first + ": " + it->second[pos];
        ++index;
    }
    return retVal;
}
