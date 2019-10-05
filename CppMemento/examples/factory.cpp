// Clean C++, page 251
// The Factory::create can be non-static, if it is necessary.

#include <iostream>
#include <memory>

class ObjectReader {
public:
    virtual ~ObjectReader() = default;
    virtual void read() = 0;
};

class FileObjectReader : public ObjectReader {
public:
    void read() override {
        std::cout << "reading object from file\n";
    }
};

class DBObjectReader : public ObjectReader {
public:
    void read() override {
        std::cout << "reading object from database\n";
    }
};

using ObjectReaderPtr = std::shared_ptr<ObjectReader>;

class ObjectReaderFactory {
public:
    enum class SorceOfStorage : int {
        FileStorage,
        DBStorage
    };

    static ObjectReaderPtr create(SorceOfStorage sorceOfStorage) {
        switch(sorceOfStorage) {
        case SorceOfStorage::FileStorage: return std::make_shared<FileObjectReader>(); break;
        case SorceOfStorage::DBStorage:
        default:
            return std::make_shared<DBObjectReader>(); break;
        }
    }
};

int main(int argc, char* argv[]) {
    ObjectReaderPtr reader = ObjectReaderFactory::create(ObjectReaderFactory::SorceOfStorage::FileStorage);
    reader->read();

    reader = ObjectReaderFactory::create(ObjectReaderFactory::SorceOfStorage::DBStorage);
    reader->read();
    return 0;
}
