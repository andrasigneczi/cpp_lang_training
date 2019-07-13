#include <iostream>
#include <vector>
#include <memory>
#include <deque>

template<class T> class Graph;

template<class T>
class Node {
public:
    Node(T value) : value_(value), processed_(false) {}
    const T& value() const { return value_; }
//    auto begin() -> decltype(Node<T>::nodeList_.begin()) const { return nodeList_.begin(); }
    typename std::vector<Node*>::const_iterator begin() const { return nodeList_.begin(); }
//    auto end() -> decltype(Node<T>::nodeList_.end()) const { return nodeList_.end(); }
    typename std::vector<Node*>::const_iterator end() const { return nodeList_.end(); }

    void setProcessed() const { processed_ = true; }
    bool processed() const { return processed_; }

private:
    friend class Graph<T>;
    void addNode(Node* node) { nodeList_.push_back(node); }
    T value_;
    std::vector<Node*> nodeList_;
    mutable bool processed_;
};

template<class T>
class Graph {
public:
    Graph(T value) : root_(value) {}
    Node<T>* root() { return &root_; }

    Node<T>* createChild(Node<T>* parent, T value) {
	nodeList.push_back(std::make_unique<Node<T>>(value));
	Node<T>* child = nodeList.back().get();
	parent->addNode(child);
	return child;
    }

    void linkNodes(Node<T>* parent, Node<T>* child) {
	parent->addNode(child);
    }

private:
    Node<T> root_;
    std::vector<std::unique_ptr<Node<T>>> nodeList;
};

void initGraph(Graph<std::string>& graph) {
    auto node1 = graph.createChild(graph.root(), "Node 1");
    auto node4 = graph.createChild(graph.root(), "Node 4");
    auto node5 = graph.createChild(graph.root(), "Node 5");
    auto node3 = graph.createChild(node1, "Node 3");
    auto node2 = graph.createChild(node3, "Node 2");

    graph.linkNodes(node1, node4);
    graph.linkNodes(node2, node1);
    graph.linkNodes(node3, node4);
}

using StrNode=Node<std::string>;
