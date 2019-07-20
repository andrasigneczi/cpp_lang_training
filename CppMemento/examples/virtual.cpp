#include <iostream>

class Base {
public:
    ~Base() { std::cout << __func__ << "\n"; }
    
};

class Derived1 : public Base {
public:
    ~Derived1() { std::cout << __func__ << "\n"; }
};

class Derived2 : public Derived1 {
public:
    virtual ~Derived2() { std::cout << __func__ << "\n"; }
};

class Derived3 : public Derived2 {
public:
    ~Derived3() { std::cout << __func__ << "\n"; }
};

int main(int argc, char* argv[]) {
    Base* d1 = new Derived2;
    delete d1;

    std::cout << std::string(80, '-') << "\n";
    Derived1* d2 = new Derived2;
    delete d2;

    std::cout << std::string(80, '-') << "\n";
    Derived2* d3 = new Derived2;
    delete d3;

    std::cout << std::string(80, '-') << "\n";
    Base* d4 = new Derived1;
    delete d4;

    std::cout << std::string(80, '-') << "\n";
    Derived1* d5 = new Derived1;
    delete d5;

    std::cout << std::string(80, '-') << "\n";
    Derived2* d6 = new Derived3;
    delete d6;

    return 0;
}
