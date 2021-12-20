#include <iostream>

struct A {virtual void f(int a = 4) = 0;};
struct B : A {virtual void f(int a = 6) {std::cout << a << std::endl;}};

class C {
public:
    virtual void f(int a = 4) = 0;
};

class D : public C {
public:
    virtual void f(int a = 6) override {std::cout << a << std::endl;}
};

int main(int argc, char* argv[]) {

    B* b = new B;
    A* a = b;
    a->f();
    b->f();
    delete a;

    D* d = new D;
    C* c = d;
    c->f();
    d->f();
    return EXIT_SUCCESS;
}
