#include <memory>

class Node;
using NodeUPtr = std::unique_ptr<Node>;
using NodeSPtr = std::shared_ptr<Node>;

class Node {
public:
    NodeUPtr node1;
    NodeSPtr node2;
};

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]) {
    Node node;
    std::unique_ptr<int> teszt = std::make_unique<int>(10);
    std::shared_ptr<int> teszt1;
    // does not work
    //teszt1 = teszt;

    std::shared_ptr<int> teszt2 = std::make_unique<int>(10);

    // does not work either
    //std::shared_ptr<int> teszt3 = teszt;

    return EXIT_SUCCESS;
}
