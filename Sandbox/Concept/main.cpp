#include <iostream>
#include <concepts>
//#include <type_traits>

std::floating_point auto testFunction(std::floating_point auto a, std::floating_point auto b) {
    return a + b;
}

template<typename T>
concept not_pointer = !std::is_pointer_v<T>;

int getObj() {
    return 0;
}


int main() {

    [[maybe_unused]] const std::floating_point auto r = testFunction(.1, .2f);
    std::cout << r << "\n";

    if(std::is_same<decltype(r), const float>()) {
	std::cout << "return type is const float\n";
    } else if(std::is_same<decltype(r), const double>()) {
	std::cout << "return type is const double\n";
    }

    [[maybe_unused]] const not_pointer auto obj = getObj();

    return EXIT_SUCCESS;
}