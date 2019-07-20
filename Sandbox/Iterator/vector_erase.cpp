#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

int main(int argc, char* argv[]) {
    std::vector<std::string> testVector{"odd1", "even2", "odd3", "even4", "odd5", "even6"};
    
    for(auto it = std::begin(testVector); it != std::end(testVector);) {
        if(it->find("odd") == 0) {
            testVector.erase(it++);
        } else {
            ++it;
        }
    }
    
    int index = 1;
    std::for_each(std::begin(testVector), std::end(testVector), [&index](const std::string& p){std::cout << index++ << ": " << p << "\n";});
    return 0;
}