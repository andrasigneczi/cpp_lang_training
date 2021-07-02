#include <gtest/gtest.h>
#include "Graph.h"
#include "GraphWithAdjacencyList.h"
#include <vector>
#include <unordered_set>

namespace {

using GraphStr = GraphWithAdjacencyList<std::string>;
using GraphStrUptr = std::unique_ptr<GraphStr>;
using GraphStrSptr = std::shared_ptr<GraphStr>;


GraphStrUptr testGraph;
GraphStr::NodeSPtr node1;
GraphStr::NodeSPtr node2;
GraphStr::NodeSPtr node3;

std::unordered_set<const GraphStr::Node*> processed;
void printAdjacent(const GraphStr::NodeSPtr& node, int depth = 0) {
    processed.insert(node.get());
    std::cout << std::setw(depth * 5) << "'" << node->value() << "'\n";
    for(auto it = node->begin(); it != node->end(); ++it) {

        if(processed.find((*it).get()) == processed.end()) {
            printAdjacent(*it, depth + 1);
        } else {
            std::cout << std::setw((depth + 1) * 5) << "'" << (*it)->value() << "'\n";
        }
    }
}

} // namespace

TEST(GRAPH, V1) {
    testGraph = std::make_unique<GraphStr>();
    node1 = testGraph->addNode("Hello");
    ASSERT_EQ(testGraph->size(), 1);
    ASSERT_EQ(node1->value(), "Hello");

    node2 = testGraph->addNode("Hello2");
    ASSERT_EQ(testGraph->size(), 2);
    ASSERT_EQ(node1->size(), 0);
    ASSERT_EQ(node2->size(), 0);
    node1->add(node2);
    ASSERT_EQ(node1->size(), 1);
    ASSERT_EQ(node2->size(), 0);
    testGraph->linkNodes(node1, node2);
    ASSERT_EQ(node1->size(), 2);
    ASSERT_EQ(node2->size(), 0);
    testGraph->linkNodes(node2, node1);
    ASSERT_EQ(node1->size(), 2);
    ASSERT_EQ(node2->size(), 1);
}

TEST(GRAPH, V2) {
    ASSERT_EQ(node1->value(), "Hello");
    ASSERT_EQ(node1->size(), 2);
    GraphStr::const_iterator it = node1->begin();
    GraphStr::NodeSPtr p = *it;
    ASSERT_NE(p.get(), nullptr);
    ASSERT_EQ(p->value(), "Hello2");
    //std::cout << p.get() << "\n";
    //std::cout << p->value() << "\n";
    ASSERT_NE(it, node1->end());
    ++it;
    p = *it;
    ASSERT_NE(p.get(), nullptr);
    ASSERT_EQ(p->value(), "Hello2");
    ASSERT_NE(it, node1->end());
    ++it;
    ASSERT_EQ(it, node1->end());
}

TEST(GRAPH, V3) {
    node3 = testGraph->addNode("Hello3");
    ASSERT_EQ(testGraph->size(), 3);
    node2->add(node3);
    ASSERT_EQ(node2->size(), 2);
    auto it = node2->begin();
    ASSERT_EQ((*it)->value(), "Hello");
    ++it;
    ASSERT_EQ((*it)->value(), "Hello3");
    it = node2->begin();
    ASSERT_EQ((*it)->value(), "Hello");
    auto it2 = it;
    ++it2;
    ASSERT_EQ((*it2)->value(), "Hello3");
    ASSERT_EQ((*it)->value(), "Hello");
}

TEST(GRAPH, WEAK_PTR_TEST) {

    class Test : public std::enable_shared_from_this<Test> {
    public:
        std::weak_ptr<Test> wptr() {
            return weak_from_this();
        }
    };

    auto p1 = std::make_shared<Test>();
    auto p2 = p1->wptr();
    ASSERT_EQ(p2.use_count(), 1);
    ASSERT_FALSE(p2.expired());
    p1 = nullptr;
    ASSERT_EQ(p2.use_count(), 0);
    ASSERT_TRUE(p2.expired());
    std::weak_ptr<Test> p3;
    ASSERT_EQ(p3.use_count(), 0);
    ASSERT_TRUE(p3.expired());
}

TEST(GRAPH, DEPTH_FIRST) {
    testGraph = std::make_unique<GraphStr>();
    node1 = testGraph->addNode("N1");
    node2 = testGraph->addNode("N2");
    node3 = testGraph->addNode("N3");

    auto node4 = testGraph->addNode("N4");
    auto node5 = testGraph->addNode("N5");
    auto node6 = testGraph->addNode("N6");
    auto node7 = testGraph->addNode("N7");
    auto node8 = testGraph->addNode("N8");
    testGraph->linkNodes(node1, node4);
    testGraph->linkNodes(node1, node5);
    testGraph->linkNodes(node2, node6);
    testGraph->linkNodes(node2, node7);
    testGraph->linkNodes(node3, node8);

    testGraph->linkNodes(node4, node5);
    testGraph->linkNodes(node5, node6);
    testGraph->linkNodes(node6, node7);
    testGraph->linkNodes(node7, node8);

    testGraph->linkNodes(node8, node7);
    testGraph->linkNodes(node7, node6);
    testGraph->linkNodes(node6, node5);
    testGraph->linkNodes(node5, node4);
    testGraph->linkNodes(node4, node1);

    //printAdjacent(node1);
    printAdjacent(node2);
    //printAdjacent(node3);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
