#include <iostream>
#include <vector>

template<typename ... T>
auto doStuff(T ... t) {
    std::cout << "call" << std::endl;
    return (t + ...);
}

template<typename ...Args>
void printer(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

template<typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args)
{
    std::cout << "push_back_vec" << std::endl;
    static_assert((std::is_constructible_v<T, Args&&> && ...));
    (v.push_back(std::forward<Args>(args)), ...);
}

// template type deduction: universal reference
template <typename T>
void f(T&& param) {
    std::cout << "param: " << param << ", type: " << typeid(T).name() << "\n";
}

int main() {
    printer(5,4,3,2,1);
    std::cout << doStuff(1, 2 ,3, 4, 5) << std::endl;

    std::vector<int> v;
    push_back_vec(v, 1, 2, 3);
    for(int i : v) std::cout << i << std::endl;

    int x = 127;
    const int cx = x;
    const int& rx = x;
    const int&& ux = 127;

    f(127);
    f(x);
    f(cx);
    f(rx);
    f(ux);

    using namespace std::literals;

    f("Hello"s);
    const char* pt = "teszt\n";
    std::cout << ++pt;

    int sum(x + cx + rx + ux);
    int sum2(10);
    std::cout << sum << "; " << sum2 << std::endl;

    return EXIT_SUCCESS;
}