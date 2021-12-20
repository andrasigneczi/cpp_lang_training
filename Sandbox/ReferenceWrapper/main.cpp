#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <functional>
#include <numeric>
#include <random>
 
int main() {
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -10);

    for(auto v : l) {
	std::cout << v << " ";
    }
    std::cout << std::endl;

    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());
    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});

    for(auto x : l) {
	std::cout << x << " ";
    }
    std::cout << std::endl;

    for(auto x : v) {
	std::cout << x << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
