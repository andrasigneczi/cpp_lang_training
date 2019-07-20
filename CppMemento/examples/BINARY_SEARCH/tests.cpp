#include "binary_search.cpp"
#include <gtest/gtest.h>
#include <random>
#include <functional>
#include <chrono>

#include <stdlib.h>
#include <time.h>

#define VECTORSIZE 1000000

int prepareVector(std::vector<int>& v, int size) {
    srand(time(0));
    v = std::vector<int>(size);
    std::for_each(v.begin(), v.end(), [](int& x){ x = rand(); });
    std::sort(v.begin(), v.end());
    return rand() % size;
}

TEST(SearchTest, ZeroItems) {
    std::vector<int> v;
    int p = binarySearch(v, 0, (int)v.size() - 1, 10);
    ASSERT_TRUE(p == -1);
}

TEST(SearchTest, OneItems) {
    std::vector<int> v{1};
    int p = binarySearch(v, 0, (int)v.size() - 1, 1);
    ASSERT_TRUE(p == 0);
}

TEST(SearchTest, TwoItemsv1) {
    std::vector<int> v{1,2};
    int p = binarySearch(v, 0, (int)v.size() - 1, 2);
    ASSERT_TRUE(p == 1);

}

TEST(SearchTest, TwoItemsv2) {
    std::vector<int> v{1,2};
    int p = binarySearch(v, 0, (int)v.size() - 1, 1);
    ASSERT_TRUE(p == 0);
}

TEST(SearchTest, OddItems) {
    std::vector<int> v;
    int p = prepareVector(v, VECTORSIZE + 1);
    int x = v[p];
    ASSERT_TRUE( p == binarySearch(v, 0, v.size() - 1, x));
}

TEST(SearchTest, EvenItems) {
    std::vector<int> v;
    int p = prepareVector(v, VECTORSIZE);
    int x = v[p];
    ASSERT_TRUE( p == binarySearch(v, 0, v.size() - 1, x));
}

TEST(SearchTest, StdFind) {
    std::vector<int> v;
    int p = prepareVector(v, VECTORSIZE);
    int x = v[p];
    auto stdR = std::find(v.begin(), v.end(), x);
    int p2 = binarySearch(v, 0, v.size() - 1, x);

    ASSERT_TRUE(stdR != v.end());
    ASSERT_TRUE(*stdR == x);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
