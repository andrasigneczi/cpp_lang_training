#include <iostream>
#include <fstream>
#include <memory>

class LoggerInterface {
public:
    virtual ~LoggerInterface() = default;
    virtual void fatal(std::string) = 0;
    virtual void error(std::string) = 0;
    virtual void warning(std::string) = 0;
    virtual void info(std::string) = 0;
    virtual void debug(std::string) = 0;
};

using Logger = std::shared_ptr<LoggerInterface>;

class ConsoleLogger : public LoggerInterface {
public:
    void fatal(std::string str) {
        std::cout << "FATAL: " << str << "\n";
    }

    void error(std::string str) {
        std::cout << "ERROR: " << str << "\n";
    }

    void warning(std::string str) {
        std::cout << "WARNING: " << str << "\n";
    }

    void info(std::string str) {
        std::cout << "INFO: " << str << "\n";
    }

    void debug(std::string str) {
        std::cout << "DEBUG: " << str << "\n";
    }
};

class MyClass {
public:
    MyClass( const Logger& logger) : logger{logger} {}
    void helloWorld() {
        logger->info("Hello World");
    }
private:
    Logger logger;
};

int main(int argc, char* argv[]) {
    Logger logger = std::make_shared<ConsoleLogger>();
    MyClass myClass(logger);
    myClass.helloWorld();
    return 0;
}
