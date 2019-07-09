#include <map>
#include <string>
#include <iostream>
#include <algorithm>

int main(int argc, char* argv[]) {
    std::map<int, std::string> testMap{{1, "odd"}, {2, "even"}, {3, "odd"}, {4, "even"}, {5, "odd"}, {6, "even"}};
    
    for(auto it = std::begin(testMap); it != std::end(testMap);) {
        if(it->second == "odd") {
            testMap.erase(it++);
        } else {
            ++it;
        }
    }
    
    std::for_each(std::begin(testMap), std::end(testMap), [](const std::pair<int,std::string>& p){std::cout << p.first << ": " << p.second << "\n";});
    return 0;
}