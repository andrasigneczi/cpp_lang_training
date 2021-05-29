#ifndef __FIBINACCI_H__
#define __FIBINACCI_H__

#include <vector>

class FibonacciIF {
public:
    virtual int generate(int n) noexcept = 0;
};

class Fibonacci_Recursive_Without_Cache final : public FibonacciIF {
public:
    int generate(int n) noexcept override;
};

class Fibonacci_Recursive_With_Cache final : public FibonacciIF{
public:
    int generate(int n) noexcept override;
private:
    int generateR(int n) noexcept;
    std::vector<int> elements;
};

class Fibonacci_Non_Recursive final : public FibonacciIF{
public:
    int generate(int n) noexcept override;
};

#endif // __FIBINACCI_H__
