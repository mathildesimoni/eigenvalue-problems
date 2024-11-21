cmake_minimum_required(VERSION 3.5.0)
project(eigenvalue-problems VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

# Update submodules if needed
set(GIT_EXECUTABLE "git")    
option(GIT_SUBMODULE "Check submodules during build" ON)
if(GIT_SUBMODULE)
  message(STATUS "Submodule update")
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive googletest WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE GIT_SUBMOD_RESULT)
  if(NOT GIT_SUBMOD_RESULT EQUAL "0")
    message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
  endif()
endif(GIT_SUBMODULE)

# Compile main
add_library(test_class
  src/test_class.cpp
)
include_directories(eigen)
add_executable(main src/main.cpp)
target_link_libraries(main test_class)

# For testing
# To activate, need to add "TESTS": "ON" for cmake.configureSettings in settings.json
option(TESTS "Activate tests" OFF)
if (TESTS)
   add_subdirectory(googletest)
   add_executable(test_example tests/test_example.cpp)
   target_link_libraries(test_example gtest_main gtest pthread test_class)

   add_custom_target(test
     COMMAND tests
     WORKING_DIRECTORY ${CMAKE_CURRENT_BUILD_DIR}
     COMMENT "Running tests")
endif(TESTS)
