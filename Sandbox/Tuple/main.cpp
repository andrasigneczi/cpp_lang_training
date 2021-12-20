#include <iostream>
#include <tuple>
#include <variant>
#include <string>
#include <iomanip>

using namespace std::literals;

template<typename T>
constexpr void isString(T&& arg) {
    using T2 = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T2, std::string>) {
	std::cout << "std::string with value " << std::quoted(arg) << '\n';
    } else {
	std::cout << "other value " << arg << '\n';
    }
}

template<typename ... I>
void test(I ... v) noexcept {
    //std::cout << sizeof ... (v) << "\n";
    std::tuple<I...> params(v ...);
    //std::cout << "Tuple 0: " << std::get<0>(params) << "\n";
    std::apply([](auto&& ... arg) mutable {
	    ((std::cout << arg << '\n'), ...);
    }, params);

    std::apply([](auto&& ... arg) {

	((isString(arg)), ...);

    }, params);
}

int main() {
    test();
    test(1);
    test(1, "Helló"s);
    test(1, "Helló", 5.5f);

    return EXIT_SUCCESS;
}