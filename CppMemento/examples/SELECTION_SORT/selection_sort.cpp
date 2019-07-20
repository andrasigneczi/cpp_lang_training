#include <iostream>
#include <vector>

void selectionSort(std::vector<int>& v) {
    if(v.size() == 0) return;
    int minIndex;
    for(size_t i = 0; i < v.size(); ++i) {
        minIndex = i;
        for(size_t j = i + 1; j < v.size(); ++j) {
            if(v[minIndex] > v[j]) minIndex = j;
        }
        if(minIndex != i) std::swap(v[i], v[minIndex]);
    }
}
