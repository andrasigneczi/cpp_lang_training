#include <iostream>
#include <memory>

#ifndef __SHARED_TEST__

class Subject;
class MyClass;
class Visitor {
public:
    virtual void visit(MyClass*){}
};

class Subject {
public:
    virtual void accept(Visitor*) = 0;
};

class MyClass : public Subject {
public:
    void accept(Visitor* v) override {
        v->visit(this);
    }
};

int main(int argc, char* argv[]) {
    MyClass myClass;
    Subject* subject = &myClass;

    class MyVisitor : public Visitor {
    public:
        void visit(MyClass* myClass) override {
            std::cout << "Subject is 'dynamic_casted' to MyClass: " << myClass << " without dynamic_cast\n";
        }

    };
    MyVisitor visitor;
    subject->accept(&visitor);
    return 0;
}

#else

#include <iostream>
#include <memory>

class Subject;
class MyClass;
class Visitor {
public:
    virtual void visit(std::shared_ptr<MyClass>){}
};

class Subject {
public:
    virtual void accept(Visitor&) = 0;
};

class MyClass : public Subject , public std::enable_shared_from_this<MyClass>{
public:
    void accept(Visitor& v) override {
        v.visit(shared_from_this());
    }
};

int main(int argc, char* argv[]) {
    std::shared_ptr<Subject> subject = std::make_shared<MyClass>();

    class MyVisitor : public Visitor {
    public:
        void visit(std::shared_ptr<MyClass> myClass) override {
            std::cout << "Subject is 'dynamic_casted' to MyClass: " << myClass.get() << " without dynamic_cast\n";
        }

    };
    MyVisitor visitor;
    subject->accept(visitor);
    return 0;
}

#endif
