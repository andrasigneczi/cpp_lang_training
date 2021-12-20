#include <iostream>

int main() {

    auto l = [](auto x) mutable {
	class Test {
	    public:
		decltype(x) a{};
		Test(decltype(x) y) : a(y) {}
		Test run() {
		    a += 22;
		    return *this;
		}
	};
	return Test(x).run();
    };

    std::cout << l(20).a << std::endl;
    return EXIT_SUCCESS;
}