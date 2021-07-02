#ifndef __GRAPHWITHADJACENCYMATRIX_H__
#define __GRAPHWITHADJACENCYMATRIX_H__

#include "Graph.h"
#include <exception>

template<typename T>
class GraphWithAdjacencyMatrix : public Graph<T> {
public:
    GraphWithAdjacencyMatrix(int size) : nodeList(size * size) {}
    class const_iteratorWAM;

    class NodeWithAdjacencyMatrix : public Graph<T>::Node, public std::enable_shared_from_this<typename GraphWithAdjacencyMatrix<T>::NodeWithAdjacencyMatrix> {
        friend class GraphWithAdjacencyMatrix;
        using GraphWithAdjacencyMatrix::Node::Node;

    public:
        void add(const std::shared_ptr<typename Graph<T>::Node>& node) noexcept override;
        size_t size() const noexcept override;
        const typename Graph<T>::const_iterator begin() const noexcept override;
        const typename Graph<T>::const_iterator end() const noexcept override;
        void accept(GraphVisitor<T>* v) const noexcept override;

    private:
        //std::vector<typename Graph<T>::NodeSPtr> nodeList;
    };

    class const_iteratorWAM : public Graph<T>::const_iterator {
        using Graph<T>::const_iterator::const_iterator;
    public:
        virtual bool operator!=(const typename Graph<T>::const_iterator& it) const noexcept override;
        virtual bool operator==(const typename Graph<T>::const_iterator& it) const noexcept override;
        virtual typename Graph<T>::const_iterator& operator++() noexcept override;
        virtual typename Graph<T>::NodeSPtr operator*() const noexcept(false) override;
        virtual void accept(GraphVisitor<T>* v) const noexcept override;
        virtual bool isEnd() const noexcept;
        virtual typename Graph<T>::const_iterator* clone() const noexcept override;
    };

    typename Graph<T>::NodeSPtr addNode(T value) noexcept override;
    void linkNodes(const typename Graph<T>::NodeSPtr& parent, const typename Graph<T>::NodeSPtr& child) noexcept override;
    size_t size() const noexcept override {return nodeList.size();}

private:
    std::vector<typename Graph<T>::NodeSPtr> nodeList;
};

#include "GraphVisitor.h"
#include "GraphWithAdjacencyMatrix.cpp"

#endif // __GRAPHWITHADJACENCYMATRIX_H__
