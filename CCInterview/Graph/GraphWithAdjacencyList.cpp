template<typename T>
void GraphWithAdjacencyList<T>::NodeWithAdjacencyList::accept(GraphVisitor<T>* v) const noexcept {
    v->visit(this);
}

template<typename T>
void GraphWithAdjacencyList<T>::const_iteratorWAL::accept(GraphVisitor<T>* v) const noexcept {
    v->visit(this);
}

template<typename T>
typename Graph<T>::NodeSPtr GraphWithAdjacencyList<T>::addNode(T value) noexcept {
    //typename Graph<T>::NodeSPtr node = std::make_shared<GraphWithAdjacencyList<T>::NodeWithAdjacencyList>(value);
    typename Graph<T>::NodeSPtr node = std::shared_ptr<GraphWithAdjacencyList<T>::NodeWithAdjacencyList>(
                new GraphWithAdjacencyList<T>::NodeWithAdjacencyList(value));
    nodeList.push_back(node);
    return node;
}

template<typename T>
void GraphWithAdjacencyList<T>::NodeWithAdjacencyList::add(const std::shared_ptr<typename Graph<T>::Node>& node) noexcept {
    nodeList.push_back(node);
}

template<typename T>
const typename Graph<T>::const_iterator GraphWithAdjacencyList<T>::NodeWithAdjacencyList::begin() const noexcept {
    typename GraphWithAdjacencyList<T>::const_iterator iter;
    if(size() > 0) {
        iter.iterator_.reset(new const_iteratorWAL());
        //iter.iterator_->parent_ = GraphWithAdjacencyList<T>::NodeWithAdjacencyList::weak_from_this();
        iter.iterator_->parent_ = this->weak_from_this();
        iter.iterator_->index_ = 0;
    }
    return iter;
}

template<typename T>
const typename Graph<T>::const_iterator GraphWithAdjacencyList<T>::NodeWithAdjacencyList::end() const noexcept {
    return typename Graph<T>::const_iterator();
}

template<typename T>
bool GraphWithAdjacencyList<T>::const_iteratorWAL::operator!=(const typename Graph<T>::const_iterator& it) const noexcept {
    return !(operator==(it));
}

template<typename T>
bool GraphWithAdjacencyList<T>::const_iteratorWAL::operator==(const typename Graph<T>::const_iterator& it) const noexcept {
    if(!it.iterator_) {
        if(isEnd()) {
            return true;
        }
        return false;
    }

    GraphVisitor<T> gv;
    it.iterator_->accept(&gv);
    const const_iteratorWAL* IT = gv.constIteratorWAL;
    //const const_iteratorWAL* IT = (const_iteratorWAL*)it.iterator_;

    if(this->parent_.expired() && IT->parent_.expired()) return true;
    if(!this->parent_.expired() && !IT->parent_.expired() && this->index_ == IT->index_) {
        auto p1 = this->parent_.lock();
        auto p2 = IT->parent_.lock();
        if(p1 == p2) return true;
    }
    return false;
}

template<typename T>
typename Graph<T>::const_iterator& GraphWithAdjacencyList<T>::const_iteratorWAL::operator++() noexcept {
    if(!this->parent_.expired()) {
        auto p = this->parent_.lock();
        if(this->index_ < p->size()) {
            ++this->index_;
        }
    }
    return *this;
}

template<typename T>
bool GraphWithAdjacencyList<T>::const_iteratorWAL::isEnd() const noexcept {
    if(auto p = this->parent_.lock()) {
        if(this->index_ < p->size()) {
            return false;
        }
    }
    return true;
}

template<typename T>
typename Graph<T>::NodeSPtr GraphWithAdjacencyList<T>::const_iteratorWAL::operator*() const noexcept(false) {
    if(isEnd()) {
        throw std::runtime_error("Graph::const_iteratorWAL: iterator is null");
    }
    //return ((NodeWithAdjacencyList*)this->parent_)->nodeList[this->index_];
    GraphVisitor<T> gv;
    if(auto p = this->parent_.lock()) {
        p->accept(&gv);
        return gv.nodeWithAdjacencyList->nodeList[this->index_];
    }
    //this->parent_->accept(&gv);
    throw std::runtime_error("Graph::const_iteratorWAL parent node is null");
}

template<typename T>
typename Graph<T>::const_iterator* GraphWithAdjacencyList<T>::const_iteratorWAL::clone() const noexcept {
    GraphWithAdjacencyList<T>::const_iteratorWAL* retVal = new GraphWithAdjacencyList<T>::const_iteratorWAL();
    retVal->parent_ = this->parent_;
    retVal->index_ = this->index_;
    return retVal;
}

template<typename T>
void GraphWithAdjacencyList<T>::linkNodes(const typename Graph<T>::NodeSPtr& parent, const typename Graph<T>::NodeSPtr& child) noexcept {
    parent->add(child);
}
