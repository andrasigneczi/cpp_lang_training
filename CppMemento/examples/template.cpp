#include <string>
#include <iostream>

template<class T>
class Simple {
public:
    void print(T x);
};

template<class T>
void Simple<T>::print(T x) {
	std::cout << x << "\n";
    }

int main(int argc, char* argv[]) {
    Simple<std::string> s;
    s.print("hello");
    return 0;
}