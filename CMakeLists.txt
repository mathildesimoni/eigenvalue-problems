cmake_minimum_required(VERSION 3.5.0)
project(eigenvalue-problems VERSION 0.1.0 LANGUAGES C CXX)

add_executable(eigenvalue-problems main.cpp)

include(CTest)
enable_testing()

