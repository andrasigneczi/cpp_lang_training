#include <iostream>
#include <memory>

#if __cplusplus <201400L
namespace std {
    template<class T, class... Args>
    unique_ptr<T> make_unique(Args&&... args) {
	return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
#endif

class System1 {
public:
    void func1() { std::cout << "System1::" << __func__ << "\n"; }
    void func2() { std::cout << "System1::" << __func__ << "\n"; }
    void func3() { std::cout << "System1::" << __func__ << "\n"; }
    void func4() { std::cout << "System1::" << __func__ << "\n"; }
};

class System2 {
public:
    void func1() { std::cout << "System2::" << __func__ << "\n"; }
    void func2() { std::cout << "System2::" << __func__ << "\n"; }
    void func3() { std::cout << "System2::" << __func__ << "\n"; }
    void func4() { std::cout << "System2::" << __func__ << "\n"; }
};

class System3 {
public:
    void func1() { std::cout << "System3::" << __func__ << "\n"; }
    void func2() { std::cout << "System3::" << __func__ << "\n"; }
    void func3() { std::cout << "System3::" << __func__ << "\n"; }
    void func4() { std::cout << "System3::" << __func__ << "\n"; }
};

class System4 {
public:
    void func1() { std::cout << "System4::" << __func__ << "\n"; }
    void func2() { std::cout << "System4::" << __func__ << "\n"; }
    void func3() { std::cout << "System4::" << __func__ << "\n"; }
    void func4() { std::cout << "System4::" << __func__ << "\n"; }
};


class Facade {
public:
    Facade() 
    : system1(std::make_unique<System1>())
    , system2(std::make_unique<System2>())
    , system3(std::make_unique<System3>())
    , system4(std::make_unique<System4>()) {}

    void method1() {
	system1->func4();
	system4->func2();
	system1->func1();
	system3->func1();
	system3->func2();
    }

    void method2() {
	system1->func3();
	system1->func2();
	system2->func4();
    }
    
private:
    std::unique_ptr<System1> system1;
    std::unique_ptr<System2> system2;
    std::unique_ptr<System3> system3;
    std::unique_ptr<System4> system4;
};

int main(int argc, char* argv[]) {
    Facade facade;
    facade.method1();
    facade.method2();
    return 0;
}
