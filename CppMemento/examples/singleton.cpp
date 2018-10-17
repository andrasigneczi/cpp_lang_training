// Clean C++ page 220

#include <iostream>

class Singleton final {
public:
    static Singleton& instance() {
	static Singleton theInstance;
	return theInstance;
    }
    void setData(int d) { _data = d; }
    int data() { return _data; }
private:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    int _data;
};

int main(int argc, char* argv[]) {
    Singleton::instance().setData(10);
    std::cout << "Data: " << Singleton::instance().data() << "\n";
    return 0;
}
