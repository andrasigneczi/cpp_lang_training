#include <variant>
#include <string>
#include <cassert>
#include <iostream>

int main() {
    std::variant<std::wstring, void const*> y(L"abc");

    using namespace std::literals;

    // casts to void const * when passed a char const *
    assert(std::holds_alternative<void const*>(y)); // succeeds
    y = L"xyz"s;
    assert(std::holds_alternative<std::wstring>(y)); // succeeds

    return EXIT_SUCCESS;
}