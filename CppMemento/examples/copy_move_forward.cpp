#include <iostream>

class Example {
public:
    Example(){}
    Example(Example& x) {
	std::cout << "Copy\n";
    }

    Example(Example&& x) {
	std::cout << "Move\n";
    }

    Example& operator=(const Example& x) {
	std::cout << "Copy assignment\n";
	return *this;
    }

    Example& operator=(Example&& x) {
	std::cout << "Move assignment\n";
	return *this;
    }
    void operator()(){}
};

template<class T>
Example factory(T&& arg) {
    return Example(std::forward<T>(arg));
} 

int main(int argc, char* argv[]) {
    Example a;
    Example b = a; // copy
    Example c(b); // copy
    a = c; // copy assignment
    a = std::move(c); // move assignment

    Example f = factory(c); // copy
    c = factory(f); // copy, move assignment

    Example d = factory(std::move(c)); // move
    c = factory(std::move(d)); // move, move assignment

    return 0;
}