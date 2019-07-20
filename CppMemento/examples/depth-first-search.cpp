#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include "graph.cpp"

// Graph search Cracing coding interview 6th Edition, page 119

void depthFirst(const StrNode* root) {
    root->setProcessed();
    std::cout << root->value() << std::endl;
    for(auto it = root->begin(); it != root->end(); ++it) {
        if((*it)->processed()) continue;
	depthFirst(*it);
    }
};

int main(int argc, char* argv[]) {
    Graph<std::string> graph("Node 0");
    initGraph(graph);
    depthFirst(graph.root());
    return 0;
}

