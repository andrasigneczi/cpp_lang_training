#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include "graph.cpp"

// Graph search Cracing coding interview 6th Edition, page 119

void breadthFirst(const StrNode* root) {
    std::deque<const StrNode*> cache;
    cache.push_back(root);
    root->setProcessed();

    while(!cache.empty()) {
	const StrNode* node = cache.front();
	cache.pop_front();
	std::cout << node->value() << std::endl;
	for(auto it = node->begin(); it != node->end(); ++it) {
	    if((*it)->processed()) continue;
	    cache.push_back(*it);
	    (*it)->setProcessed();
	}
    }
}

int main(int argc, char* argv[]) {
    Graph<std::string> graph("Node 0");
    initGraph(graph);
    breadthFirst(graph.root());
    return 0;
}

