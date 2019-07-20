#include "quick_sort.cpp"
#include <gtest/gtest.h>
#include <random>
#include <functional>
#include <chrono>

#include <stdlib.h>
#include <time.h>

/*
TEST(SquareRootTest, PositiveNos) { 
    ASSERT_EQ(6, squareRoot(36.0));
    ASSERT_EQ(18.0, squareRoot(324.0));
    ASSERT_EQ(25.4, squareRoot(645.16));
    ASSERT_EQ(0, squareRoot(0.0));
}

TEST(SquareRootTest, NegativeNos) {
    ASSERT_EQ(-1.0, squareRoot(-15.0));
    ASSERT_EQ(-1.0, squareRoot(-0.2));
}
*/

TEST(SortTest, ZeroItems) {
    std::vector<int> v;
    quickSort(v, 0, (int)v.size() - 1);
    ASSERT_TRUE(true);
}

TEST(SortTest, OneItems) {
    std::vector<int> v{1};
    quickSort(v, 0, (int)v.size() - 1);
    ASSERT_TRUE(v.size() == 1);
    ASSERT_TRUE(v[0] == 1);
}

TEST(SortTest, TwoItemsv1) {
    std::vector<int> v{1,2};
    quickSort(v, 0, (int)v.size() - 1);
    ASSERT_TRUE(v.size() == 2);
    ASSERT_TRUE(v[0] == 1);
    ASSERT_TRUE(v[1] == 2);

}

TEST(SortTest, TwoItemsv2) {
    std::vector<int> v{2,1};
    quickSort(v, 0, (int)v.size() - 1);
    ASSERT_TRUE(v.size() == 2);
    ASSERT_TRUE(v[0] == 1);
    ASSERT_TRUE(v[1] == 2);
}

TEST(SortTest, OddItems) {
/*
    using my_engine = std::default_random_engine;
    using my_distribution = std::uniform_int_distribution<>; // type of engine
    // type of distribution
    my_engine re {};
    my_distribution one_to_six {1,6};
    auto die = std::bind(one_to_six,re); // the default engine
    // distribution that maps to the ints 1..6
    // make a generator
    
*/
    std::vector<int> v(1000001);


    srand(time(0));
    std::for_each(v.begin(), v.end(), [](int& x){ x = rand(); });

    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //auto die = std::bind(std::uniform_int_distribution<>{0,std::numeric_limits<int>::max()}, std::default_random_engine{seed});
    //auto die = std::bind(std::normal_distribution<>{0,std::numeric_limits<int>::max()}, std::default_random_engine{seed});
    //std::for_each(v.begin(), v.end(), [&die](int& x){ x = die(); });

    quickSort(v, 0, (int)v.size() - 1);
    for(size_t i = 1; i < v.size(); ++i) {
	ASSERT_TRUE(v[i - 1] <= v[i]);
    }
}

TEST(SortTest, EvenItems) {
    srand(time(0));

    std::vector<int> v(1000000);
    std::for_each(v.begin(), v.end(), [](int& x){ x = rand(); });
    quickSort(v, 0, (int)v.size() - 1);
    for(size_t i = 1; i < v.size(); ++i) {
	ASSERT_TRUE(v[i - 1] <= v[i]);
    }
}

TEST(SortTest, StdSort) {
    srand(time(0));

    std::vector<int> v(1000000);
    std::for_each(v.begin(), v.end(), [](int& x){ x = rand(); });
    std::sort(v.begin(), v.end());
    for(size_t i = 1; i < v.size(); ++i) {
	ASSERT_TRUE(v[i - 1] <= v[i]);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
