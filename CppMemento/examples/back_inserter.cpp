#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


int main(int argc, char* argv[]) {
    std::vector<int> a{1,2,3,4,5,6,7,8,9};
    std::vector<int> b{0};

    std::copy(a.begin(),a.end(), std::back_inserter(b));
    std::copy(b.begin(), b.end(), std::ostream_iterator<decltype(b.at(0))>(std::cout, ","));
    std::cout << "\n";
    return 0;
}