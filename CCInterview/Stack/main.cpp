#include "Stack.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Stack<int> s;
    s << 1 << 2 <<3;
    std::cout << s.size() << std::endl;
    
    return 0;
}