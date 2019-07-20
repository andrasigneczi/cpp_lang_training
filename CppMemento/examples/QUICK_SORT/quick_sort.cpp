#include <iostream>
#include <vector>

int partition(std::vector<int>& v, int first, int last) {
    int pivot = v[(first + last) / 2];

    while(first <= last) {
	while(v[first] < pivot) ++first;
	while(v[last] > pivot) --last;
	if(first <= last) {
	    std::swap(v[first], v[last]);
	    ++first;
	    --last;
	}
    }
    return first;
}

void quickSort(std::vector<int>& v, int first, int last) {
    if(v.size() == 0) return;
    int index = partition(v, first, last);
    if(first < index - 1) {
	quickSort(v, first, index - 1);
    }
    if(index < last) {
	quickSort(v, index, last);
    }
}
