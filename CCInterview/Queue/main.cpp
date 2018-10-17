#include "Queue.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Queue<int> q;
    q << 1 << 2 <<3;
    std::cout << q.size() <<std::endl;
    return 0;
}