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

set(SOURCE_FILES
  src/main.cpp
  src/test_class.cpp
  src/Config.cpp
  src/MatrixGeneratorFromFile.cpp
  src/FileReaderCSV.cpp
  src/FileReaderTXT.cpp
  src/FileReaderMTX.cpp
  src/MatrixGeneratorFromFunction.cpp
  src/FunctionManager.cpp
  src/OutputGenerator.cpp
  src/AbstractIterativeSolver.cpp
  src/PowerMethodSolver.cpp
  src/InversePowerMethodSolver.cpp
  src/OutputGenerator.cpp
)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main yaml-cpp)

<<<<<<< HEAD
=======
target_link_libraries(config yaml-cpp)

add_executable(main src/main.cpp)
target_link_libraries(main test_class config matrix_generator_from_file file_reader_csv file_reader_txt file_reader_mtx matrix_generator_from_function function_manager abstract_iterative_solver power_method inverse_power_method)
>>>>>>> 6cd1713 (allow homogenous templated output for solver function and test in main)

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
