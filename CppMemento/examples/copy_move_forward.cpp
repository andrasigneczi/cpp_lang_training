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

};

template<class T> Example factory(T&& arg) {
    return Example(std::forward<T>(arg));
} 

int main(int argc, char* argv[]) {
    Example a;
    Example b = a;
    Example c(b);
    a = c;
    a = std::move(c);

    factory(c);
    factory(std::move(c));
    return 0;
}