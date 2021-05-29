cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -Wextra -Werror -Wno-unused-function -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Werror -Wno-unused-function -fPIC")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} .)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests fibonacci_test.cpp
                        fibonacci.cpp)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
