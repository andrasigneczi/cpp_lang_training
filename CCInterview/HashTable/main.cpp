#include <iostream>
#include "HashTable.h"
#include <vector>

int main(int argc, char* argv[]) {
    HashTable h;
    
    h["hello"] = "elso";
    if( h.keyCount() != 1 ) std::cout << "Error1\n";
    h["bello"] = "masodik";
    if( h.keyCount() != 2 ) std::cout << "Error2\n";
    h["helol"] = "harmadik";
    if( h.keyCount() != 3 ) std::cout << "Error3\n";
    
    std::cout << "'" << h["hello"] << "' '" << h["bello"] << "' '" << h["helol"] << "' '" << h["negyedik"] << "'\n";
    if( h.keyCount() != 4 ) std::cout << "Error4\n";
    
    std::vector<std::string> keys{ "hello", "bello", "helol", "negyedik" };
    
    for( auto key : keys ) {
        if(h.find(key)) {
            std::cout << "removing '" << key << "'\n";
            int keyCount = h.keyCount();
            if( !h.remove(key))  std::cout << "Error6\n";
            if( h.keyCount() != keyCount - 1 ) std::cout << "Error5\n";
            if(h.find(key)) std::cout <<"remove " << key << " failed\n";
        }
    }
    
    return 0;
}