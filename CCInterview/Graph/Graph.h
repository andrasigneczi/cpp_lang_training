#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <memory>

template<typename T>
class GraphVisitor;

template<typename T>
class Graph {
public:

    class const_iterator;

    class Node {
        friend class Graph;
    protected:
        Node(T v) : value_(v) {}

    public:
        virtual void add(const std::shared_ptr<Node>& node) noexcept = 0;
        virtual size_t size() const noexcept = 0;
        virtual const const_iterator begin() const noexcept = 0;
        virtual const const_iterator end() const noexcept = 0;
        virtual const T value() const noexcept {return value_;}
        virtual void accept(GraphVisitor<T>*) const noexcept{}
    private:
        T value_;
    };

    using NodeUPtr = std::unique_ptr<Node>;
    using NodeSPtr = std::shared_ptr<Node>;

    class const_iterator {
    public:
        const_iterator() = default;
        const_iterator(Node* p) : parent_(p){}
        virtual ~const_iterator() = default;
        virtual bool operator!=(const const_iterator& it) const noexcept {
            if(iterator_) {
                return iterator_->operator!=(it);
            }
            if(it.iterator_) return true;
            return false;
        }
        virtual bool operator==(const const_iterator& it) const noexcept {
            if(iterator_) {
                return iterator_->operator==(it);
            }
            if(!it.iterator_) return true;
            return false;
        }
        virtual const_iterator& operator++() noexcept {
            if(iterator_) {
                iterator_->operator++();
            }
            return *this;
        }
        virtual NodeSPtr operator*() const noexcept(false) {
            if(iterator_) {
                return iterator_->operator*();
            }
            else {
                return NodeSPtr();
            }
        }

        const_iterator(const const_iterator& it) noexcept {
            if(it.iterator_) {
                iterator_ = std::unique_ptr<const_iterator>(it.iterator_->clone());
            } else {
                iterator_.reset(nullptr);
            }
            parent_ = it.parent_;
            index_ = it.index_;
        }

        virtual const_iterator& operator=(const const_iterator& it) noexcept {
            if(it.iterator_) {
                iterator_ = std::unique_ptr<const_iterator>(it.iterator_->clone());
            } else {
                iterator_.reset(nullptr);
            }
            parent_ = it.parent_;
            index_ = it.index_;
            return *this;
        }

        virtual void accept(GraphVisitor<T>*) const noexcept {}
        virtual bool isEnd() const noexcept {return !iterator_ || parent_.expired();}
        virtual const_iterator* clone() const noexcept {return nullptr;}

        std::unique_ptr<const_iterator> iterator_;

        std::weak_ptr<const Node> parent_;
        size_t index_{0};
    };

    virtual NodeSPtr addNode(T value) noexcept = 0;
    virtual void linkNodes(const NodeSPtr& n1, const NodeSPtr& n2) noexcept = 0;
    virtual size_t size() const noexcept = 0;
};

#endif // __GRAPH_H__
