#include <algorithm>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string str("aabb");
    
    do {
	std::cout << str << std::endl;
    } while(std::next_permutation(str.begin(), str.end()));
    return 0;
}
