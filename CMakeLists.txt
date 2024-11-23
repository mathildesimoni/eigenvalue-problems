cmake_minimum_required(VERSION 3.5.0)
project(eigenvalue-problems VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

# Update submodules if needed
set(GIT_EXECUTABLE "git")    
option(GIT_SUBMODULE "Check submodules during build" ON)
if(GIT_SUBMODULE)
  message(STATUS "Submodule update")
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive eigen WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE GIT_SUBMOD_RESULT)
  if(NOT GIT_SUBMOD_RESULT EQUAL "0")
    message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
  endif()
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive googletest WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE GIT_SUBMOD_RESULT)
  if(NOT GIT_SUBMOD_RESULT EQUAL "0")
    message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
  endif()
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive yaml-cpp WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE GIT_SUBMOD_RESULT)
  if(NOT GIT_SUBMOD_RESULT EQUAL "0")
    message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
  endif()
endif(GIT_SUBMODULE)

# Compile main
add_subdirectory(yaml-cpp)
include_directories(eigen)

add_library(test_class
  src/test_class.cpp
)
add_library(config
  src/Config.cpp
)
add_library(matrix_generator_from_file
  src/MatrixGeneratorFromFile.cpp
)
add_library(file_reader_csv
  src/FileReaderCSV.cpp
)
add_library(file_reader_txt
  src/FileReaderTXT.cpp
)
add_library(file_reader_mtx
  src/FileReaderMTX.cpp
)

add_library(matrix_generator_from_function
  src/MatrixGeneratorFromFunction.cpp
)
add_library(function_manager
  src/FunctionManager.cpp
)

add_library(abstract_iterative_solver
  src/AbstractIterativeSolver.cpp
)
add_library(power_method
  src/PowerMethodSolver.cpp
)
add_library(power_method_shift
  src/PowerMethodSolverShift.cpp
)

target_link_libraries(config yaml-cpp)

add_executable(main src/main.cpp)
target_link_libraries(main test_class config matrix_generator_from_file file_reader_csv file_reader_txt file_reader_mtx matrix_generator_from_function function_manager)

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

# For documentation
# To activate, need to add "DOCUMENTATION": "ON" for cmake.configureSettings in settings.json
option(DOCUMENTATION "Activate documentation" OFF)
if (DOCUMENTATION)
   set(DOXYGEN_EXECUTABLE doxygen)
   set(DOXYFILE Doxyfile)
   add_custom_target(doc_doxygen ALL
     COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${DOXYFILE}
     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
     COMMENT "Generating API documentation with Doxygen"
     VERBATIM)
endif(DOCUMENTATION)
