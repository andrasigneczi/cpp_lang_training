// double-ended-queue
#include <iostream>
#include <deque>
#include <iterator>

class Element {
public:
    explicit Element(int n) : num(n) {}
    operator int() const { return num; }

private:
    int num;
};

int main(int argc, char* argv[]) {
    std::deque<Element> deque;
    deque.push_back(Element(1));
    deque.push_front(Element{2});

    deque.emplace_back(3);
    deque.emplace_front(4);

    for(auto it=deque.begin(); it != deque.end(); ++it) {
	std::cout << *it << std::endl;
    }

    std::copy(deque.begin(), deque.end(), std::ostream_iterator<Element>(std::cout, " "));
    std::cout << "\n";

    std::cout << "front: " << deque.front() << "\n";
    std::cout << "back: " << deque.back() << "\n";
    std::cout << "at(1): " << deque.at(1) << "\n";
    std::cout << "operator[1]: " << deque[1] << "\n";

    deque.pop_front();
    deque.pop_back();

    deque.emplace(deque.begin() + 1, 22);

    std::copy(deque.begin(), deque.end(), std::ostream_iterator<Element>(std::cout, " "));
    std::cout << "\n";

    return 0;
}
