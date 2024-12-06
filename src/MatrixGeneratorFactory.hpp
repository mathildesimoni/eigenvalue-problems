#ifndef __MATRIX_FACTORY_HPP__
#define __MATRIX_FACTORY_HPP__

#include <iostream>
#include <string>
#include "constants.hpp"
#include "MatrixGenerator.hpp"

// Factory class for creating matrices
template <typename T>
class MatrixGeneratorFactory
{
public:
    MatrixGeneratorFactory(const std::string &input_name, const std::vector<std::string> &input_args) : input_name(input_name), input_args(input_args) {}; /**< Constructor */
    ~MatrixGeneratorFactory() {};                                                                                                                          /**< Destructor */
    std::unique_ptr<MatrixGenerator<T>> choose_generator();

private:
    // Helper functions
    std::unique_ptr<MatrixGenerator<T>> choose_function_generator(); // TODO: return child class instead????
    std::unique_ptr<MatrixGenerator<T>> choose_file_generator();
    const std::string &input_name;
    const std::vector<std::string> &input_args;
};

#endif