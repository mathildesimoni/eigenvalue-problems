cmake_minimum_required(VERSION 3.5.0)
project(eigenvalue-problems VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

# UPDATE SUBMODULES IF NEEDED
add_subdirectory(lib)

# COMPILE MAIN EXECUTABLE
add_subdirectory(lib/yaml-cpp)
include_directories(lib/eigen)
include_directories(include)

set(SOURCE_FILES
  src/main.cpp
  src/Config.cpp
  src/MatrixGeneratorFromFile.cpp
  src/FileReaderCSV.cpp
  src/FileReaderTXT.cpp
  src/FileReaderMTX.cpp
  src/MatrixGeneratorFromFunction.cpp
  src/FunctionManager.cpp
  src/OutputGenerator.cpp
  src/SolverFactory.cpp
  src/AbstractIterativeSolver.cpp
  src/PowerMethodSolver.cpp
  src/InversePowerMethodSolver.cpp
  src/QrMethodSolver.cpp
  src/OutputGenerator.cpp
  src/MatrixGeneratorFactory.cpp
)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main yaml-cpp)

# TESTING
add_subdirectory(lib/googletest)
add_subdirectory(tests)

# DOCUMENTATION
add_subdirectory(doc)