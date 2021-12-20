#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

class Test {
public:
    template<typename T>
    void f1(T&& name) {
	names_.push_back(std::forward<T>(name));
    }

    std::vector<std::string> names_;
};

int main() {
    Test t;
    t.f1("Hello");
    t.f1("World"s);

    auto v = "!!!"s;
    t.f1(v);

    for(auto& x : t.names_) std::cout << x << "\n";
    return EXIT_SUCCESS;
}