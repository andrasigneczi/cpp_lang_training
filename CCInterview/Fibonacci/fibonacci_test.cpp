#include <gtest/gtest.h>
#include "fibonacci.h"

constexpr int fibNum = 30;
constexpr int expectedResult = 832040;

TEST(Fibonacci, Recursive_Without_Cache) {
    Fibonacci_Recursive_Without_Cache fib;
    ASSERT_EQ(fib.generate(fibNum), expectedResult);
}

TEST(Fibonacci, Recursive_With_Cache) {
    Fibonacci_Recursive_With_Cache fib;
    ASSERT_EQ(fib.generate(fibNum), expectedResult);
}

TEST(Fibonacci, Non_Recursive) {
    Fibonacci_Non_Recursive fib;
    ASSERT_EQ(fib.generate(fibNum), expectedResult);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
