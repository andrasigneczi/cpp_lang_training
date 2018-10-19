#include <thread>
#include <mutex>
#include <iostream>
#include <unistd.h>

void func1(int a) {
    usleep(1e+3);
    for(int i = 0; i < a; ++i) {
        std::cout << __FUNCTION__ << " " << i << "\n";
        usleep(1e+1);
    }
}

void func2(int a) {
    usleep(1e+3);
    for(int i = 0; i < a; ++i) {
        std::cout << __FUNCTION__ << " " << i << "\n";
        usleep(1e+1);
    }
}

int main(int argc, char* argv[]) {
    std::thread t1(func1,1e+3);
    std::thread t2(func2,1e+3);
    
    t1.join();
    t2.join();
}