#include <iostream>
#include <stdlib.h>
#include <stdexcept>

void TerminateCb()
{
    std::cout << "Terminate\n";
}

void AtExitCb()
{
    std::cout << "atexit\n";
}

class Test {
public:
    Test() { throw std::runtime_error("haha"); }

    static void* operator new(std::size_t s, int param) {
	std::cout << "operator new: " << param << std::endl;
	return ::operator new(s);
    }

    static void operator delete(void* p, int param) {
	    std::cout << "operator delete: " << param << std::endl;
	::operator delete(p);
    }
};

class Test2 {
public:
    static void* operator new[](std::size_t s) {
	std::cout << "operator new[]"  << std::endl;
	return ::operator new(s);
    }

    static void operator delete[](void* p) {
	    std::cout << "operator delete[]" << std::endl;
	::operator delete(p);
    }
};



int main(int argc, char *argv[]) {
    std::set_terminate( TerminateCb );
    atexit( AtExitCb );

    try {
	Test* t = new (11) Test;
	//delete (false) t;
    } catch(const std::exception& e) {
	std::cout << e.what() << std::endl;
    }

    Test2* t2 = new Test2[10];
    delete [] t2;
    return 0;
}
