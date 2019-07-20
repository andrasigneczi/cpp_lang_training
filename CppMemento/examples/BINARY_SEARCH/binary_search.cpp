#include <iostream>
#include <vector>

template<typename T>
int binarySearch(const std::vector<T>& v, int first, int last, T x) {
    if(last < first) return -1;
    int midpoint = (first + last) / 2;

    if(v[midpoint] == x) return midpoint;
    if(v[midpoint] > x) return binarySearch(v, first, midpoint - 1, x);
    return binarySearch(v, midpoint + 1, last, x);
}
