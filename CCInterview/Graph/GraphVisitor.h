#ifndef __GRAPHVISITOR_H__
#define __GRAPHVISITOR_H__

//#include "GraphWithAdjacencyList.h"

template<typename T>
class GraphVisitor {
public:
    virtual void visit(const typename GraphWithAdjacencyList<T>::NodeWithAdjacencyList* p) {
        nodeWithAdjacencyList = p;
    }
    virtual void visit(const typename GraphWithAdjacencyList<T>::const_iteratorWAL* p) {
        constIteratorWAL = p;
    }
    const typename GraphWithAdjacencyList<T>::const_iteratorWAL* constIteratorWAL;
    const typename GraphWithAdjacencyList<T>::NodeWithAdjacencyList* nodeWithAdjacencyList;
};

#endif
