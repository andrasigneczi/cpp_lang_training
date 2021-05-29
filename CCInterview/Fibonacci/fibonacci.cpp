#include "fibonacci.h"

int Fibonacci_Recursive_Without_Cache::generate(int n) noexcept {
    if(n == 0 || n == 1) return n;
    return generate(n - 1) + generate(n - 2);
}

// -------------------------------------------------------------------

int Fibonacci_Recursive_With_Cache::generate(int n) noexcept {
    elements = std::vector<int>(n + 1);
    elements[1] = 1;
    return generateR(n);
}

int Fibonacci_Recursive_With_Cache::generateR(int n) noexcept {
    if(n == 0 || n == 1) return n;
    if(elements[n] > 0) {
        return elements[n];
    }
    elements[n] = generateR(n - 1) + generateR(n - 2);
    return elements[n];
}

// -------------------------------------------------------------------

int Fibonacci_Non_Recursive::generate(int n) noexcept {
    if(n == 0 || n == 1) return n;
    int first = 0;
    int second = 1;
    int retV = 0;
    for(int i = 2; i <= n; ++i) {
        retV = first + second;
        first = second;
        second = retV;
    }
    return retV;
}
