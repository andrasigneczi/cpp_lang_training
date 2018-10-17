// My Drive >> Development >> Java >> Design Patterns

#include <iostream>
#include <memory>

// ------------------------------------------------------------
class NullObject {
public:
    virtual bool isNull() const = 0;
};

class Fruit : public NullObject {
public:
    Fruit(): numberOfFruits(0) {}
    Fruit(int n) : numberOfFruits(n) {}
    bool isNull() const { return numberOfFruits == 0; }
    Fruit& operator==(int n) { numberOfFruits = n; }

private:
    int numberOfFruits;
};
// -----------------------------------------------------------

class AbstractDocument {
public:
    virtual bool isNull() const noexcept = 0;
    virtual std::string author() = 0;
    virtual std::string title() = 0;
    virtual void setAuthor(std::string) {}
    virtual void setTitle(std::string) {}
};

class NullDocument final : public AbstractDocument {
public:
    bool isNull() const noexcept override { return true; }
    std::string author() override { return notAvailable; }
    std::string title() override { return notAvailable; }
private:
    static const std::string notAvailable;
};

const std::string NullDocument::notAvailable = "Not available";


class RealDocument : public AbstractDocument {
public:
    RealDocument(std::string a, std::string t) : _author(a), _title(t) {}
    bool isNull() const noexcept override { return false; }
    std::string author() override { return _author; }
    std::string title() override { return _title; }
    void setAuthor(std::string a) override {_author = a;}
    void setTitle(std::string t) override {_title = t;}

private:
    std::string _author;
    std::string _title;
};

std::unique_ptr<AbstractDocument> genDocument(std::string nickName) {
    if(nickName == "C++ Bible") return std::make_unique<RealDocument>("Bjarne Stroustrup", "The C++ Programming Language");
    if(nickName == "Clean C++") return std::make_unique<RealDocument>("Stephan Roth", "Clean C++");
    return std::make_unique<NullDocument>();
}

int main(int argc, char* argv[]) {

    Fruit f;
    if(f.isNull()) { std::cout << "Null\n"; } else { std::cout << "Not Null\n"; }
    f = 10;
    if(f.isNull()) { std::cout << "Null\n"; } else { std::cout << "Not Null\n"; }

    std::unique_ptr<AbstractDocument> d = genDocument("C++ Bible");
    if(d->isNull()) { std::cout << "Document is null\n"; } else { std::cout << "Document is not Null\n"; }
    std::cout << "Author: " << d->author() << "\n";
    std::cout << "Title: " << d->title() << "\n";

    d =  genDocument("");
    if(d->isNull()) { std::cout << "Document is null\n"; } else { std::cout << "Document is not Null\n"; }
    std::cout << "Author: " << d->author() << "\n";
    std::cout << "Title: " << d->title() << "\n";
    return 0;
}
