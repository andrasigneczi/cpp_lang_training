#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>

struct Element {
    int a;
    int b;
};

bool operator==(const Element& e1, const Element& e2) {
    return e1.a == e2.a && e1.b == e2.b;
}

namespace std {
    template<> struct hash<Element> {
	std::size_t operator()(Element const & s) const noexcept {
	    return s.a ^ (s.b << 1);
	}
    };
}

int main(int argc, char*argv[]) {
    
    //std::unordered_map<Element,std::string, std::hash<Element>> mymap;
    std::unordered_map<Element,std::string> mymap;
    mymap.emplace(Element{10,11}, "hello");
    std::cout << "map size: " <<  mymap.size() << "\n";
    std::cout << "first key a: " << mymap.begin()->first.a << "\n";
    std::cout << "first key b: " << mymap.begin()->first.b << "\n";
    std::cout << "first value: " << mymap.begin()->second << "\n";
    return 0;
}