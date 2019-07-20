#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
auto Sort(std::vector<T>& vec) -> decltype(vec.begin()) {
    std::sort(vec.begin(), vec.end());
    return vec.begin();
}

int main(int argc, char* argv[]) {
    std::vector<int> vec{9,5,11,-2};
    using iter=decltype(vec.begin());
    for(iter it=Sort(vec); it != vec.end(); ++it) {
	std::cout << *it << "\n";
    }
    return 0;
}
