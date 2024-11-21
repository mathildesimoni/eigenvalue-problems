cmake_minimum_required(VERSION 3.5.0)
project(eigenvalue-problems VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(test_class
  src/test_class.cpp
)

include_directories(eigen)
add_subdirectory(googletest)

add_executable(main src/main.cpp)
target_link_libraries(main test_class)

add_executable(test_example tests/test_example.cpp)
target_link_libraries(test_example gtest_main gtest pthread test_class)

add_custom_target(test ./test_example DEPENDS test_example)

