#include <any>
#include <iostream>

int main() {
    std::cout << std::boolalpha;

    std::any a = 3.14f;

    std::cout << a.type().name() << std::any_cast<float>(a) << "\n";
    
    auto b = std::any_cast<float>(&a);

    std::cout << *b << std::endl;

    return EXIT_SUCCESS;
}