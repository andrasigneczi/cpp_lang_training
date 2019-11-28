#include <iostream>
#include <memory>
#include <chrono>

#define ITERATION 1e+8
#ifdef __PTR_TEST__

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
    auto c1 = std::chrono::high_resolution_clock::now();
    int counter = 0;
    for(int i = 0; i < ITERATION; ++i) {
        MyClass myClass;
        Subject* subject = &myClass;

        class MyVisitor : public Visitor {
        public:
            MyVisitor(int& counter) : counter(counter) {}
            void visit(MyClass* myClass) override {
                //std::cout << "Subject is 'dynamic_casted' to MyClass: " << myClass << " without dynamic_cast\n";
                ++counter;
            }
        private:
            int& counter;
        };
        MyVisitor visitor(counter);
        subject->accept(&visitor);
    }
    std::cout << "counter: " << counter << "\n";
    auto c2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(c2 - c1).count() << " microseconds\n";
    return 0;
}

#elif defined __SHARED_TEST__

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
    auto c1 = std::chrono::high_resolution_clock::now();
    int counter = 0;
    for(int i = 0; i < ITERATION; ++i) {
        std::shared_ptr<Subject> subject = std::make_shared<MyClass>();

        class MyVisitor : public Visitor {
        public:
            MyVisitor(int& counter) : counter(counter) {}
            void visit(std::shared_ptr<MyClass> myClass) override {
                //std::cout << "Subject is 'dynamic_casted' to MyClass: " << myClass.get() << " without dynamic_cast\n";
                ++counter;
            }
        private:
            int& counter;
        };
        MyVisitor visitor(counter);
        subject->accept(visitor);
    }
    std::cout << "counter: " << counter << "\n";
    auto c2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(c2 - c1).count() << " microseconds\n";
    return 0;
}

#elif defined __DYNAMIC_TEST__
class Subject {
public:
    virtual void accept() {}
};

class MyClass : public Subject {
public:
    MyClass(int& counter) : counter(counter) {}
    void accept() override {
        ++counter;
    }
    int& counter;
};

int main(int argc, char* argv[]) {
    auto c1 = std::chrono::high_resolution_clock::now();
    int counter = 0;
    for(int i = 0; i < ITERATION; ++i) {
        MyClass myClass(counter);
        Subject* subject = &myClass;

        dynamic_cast<MyClass*>(subject)->accept();
    }
    std::cout << "counter: " << counter << "\n";
    auto c2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(c2 - c1).count() << " microseconds\n";
    return 0;
}

#endif
