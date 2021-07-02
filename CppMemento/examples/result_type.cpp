#ifndef RESULT_TYPE_H
#define RESULT_TYPE_H

#include <stdlib.h>
#include <type_traits>
#include <iostream>
#include <iomanip>
#include <algorithm>

template<typename T1, typename T2>
bool isSameBaseType(T1, T2) {
    //return std::is_same<std::remove_cv<std::remove_reference<T1>::type>::type, std::remove_cv<std::remove_reference<T2>::type>::type>();
    return std::is_same<std::remove_cv<std::remove_reference<T1>>, std::remove_cv<std::remove_reference<T2>>>();
}

int spec(int n) {
    return n == 10;
}

int t1() {
    return 10;
}

int& t2() {
    static int n = 10;
    return n;
}

const std::string& t3() {
    static const std::string n("10");
    return n;
}

const std::string t4() {
    return "Hello";
}

template <typename First, typename Second>
bool anyOf(First&& first, Second&& second) {
    return first == second;
}

template <typename V, typename First, typename... Rest>
bool anyOf(V&& val, First&& first, Rest... rest) {
    return val == first || anyOf(std::forward<V>(val), std::forward<Rest>(rest)...);
}

template <typename V, typename... Rest>
bool noneOf(V&& val, Rest... rest) {
    return !anyOf(std::forward<V>(val), std::forward<Rest>(rest)...);
}

int main(int argc, char* argv[]) {

    std::cout << std::setw(10) << std::is_same<int, int32_t>() << "\n";
    std::cout << std::setw(10) << std::is_same<int, const int32_t>() << "\n";
    std::cout << std::setw(10) << std::is_same<int, volatile int32_t>() << "\n";
    std::cout << std::setw(10) << std::is_same<int, int32_t&>() << "\n";
    std::cout << std::setw(10) << std::is_same<int, int32_t&&>() << "\n";

    int x = 20;
    volatile const int32_t& y = x;
    std::cout << std::setw(10) << isSameBaseType(x, y) << "\n";

    std::array<int, 5> testA{5,7,9,10,11};
    if(std::any_of(testA.begin(), testA.end(), spec)) {
        std::cout << std::setw(10) << "T1 Any of true\n";
    }

    if(!std::any_of(testA.begin(), testA.end(), [](int n){return n == 100;})) {
        std::cout << std::setw(10) << "T2 Any of false\n";
    }

    if(anyOf(x, 5, 7, 9, 10, 11, 20)) {
        std::cout << std::setw(10) << "T3 Any of true\n";
    }

    if(anyOf(t1(), 5, 7, 9, 10, 11, 20)) {
        std::cout << std::setw(10) << "T4 Any of true\n";
    }

    if(!anyOf(t1(), 5, 7, 9, 11, 20)) {
        std::cout << std::setw(10) << "T5 Any of false\n";
    }

    if(anyOf(t2(), 5, 7, 9, 10, 11, 20)) {
        std::cout << std::setw(10) << "T6 Any of true\n";
    }

    if(!anyOf(t2(), 5, 7, 9, 11, 20)) {
        std::cout << std::setw(10) << "T7 Any of false\n";
    }

    if(anyOf(t3(), "5", "7", "9", "10", "11", "20")) {
        std::cout << std::setw(10) << "T8 Any of true\n";
    }

    if(!anyOf(t3(), "5", "7", "9", "11", "20")) {
        std::cout << std::setw(10) << "T9 Any of true\n";
    }

    if(anyOf(t4(), "Hello", "7", "9", "11", "20")) {
        std::cout << std::setw(10) << "T10 Any of true\n";
    }

    if(anyOf(t4(), "Hello")) {
        std::cout << std::setw(10) << "T11 Any of true\n";
    }

    if(!noneOf(t4(), "Hello")) {
        std::cout << std::setw(10) << "T12 Any of true\n";
    }

    if(!noneOf(t4(), "Bello", "Hello")) {
        std::cout << std::setw(10) << "T13 Any of true\n";
    }

    return EXIT_SUCCESS;
}

#endif // RESULT_TYPE_H
