#include <iostream>


class Liter {
public:
    Liter(int value) : value_(value) {}
    const int value() const { return value_; }
private:
    int value_;
};

/*
    The declaration of a literal operator shall have a parameter-declaration-clause equivalent to one of the following:

    const char*
    unsigned long long int
    long double
    char
    wchar_t
    char16_t
    char32_t
    const char*, std::size_t
    const wchar_t*, std::size_t
    const char16_t*, std::size_t
    const char32_t*, std::size_t
*/
Liter operator"" _l(unsigned long long int v) { return Liter(v); }

std::ostream& operator<<(std::ostream& o, const Liter& l) {
    o << std::to_string(l.value()) + " liter";
    return o;
}

int main(int argc, char* argv[]) {
    std::cout << 10_l << "\n";
    return 0;
}
