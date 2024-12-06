#include "MatrixGeneratorFromFunction.hpp"
#include "FunctionManager.hpp"
#include <iostream>

// Constructor
template <typename T>
MatrixGeneratorFromFunction<T>::MatrixGeneratorFromFunction(const std::vector<std::string> &input_args)
{
    // Check that the vector has exactly 3 argument, otherwise throw an error and cast the last 2 to ints
    if (input_args.size() != 3)
        throw std::invalid_argument("Expected exactly 3 arguments (function name, number of rows, number of columns), but got " + std::to_string(input_args.size()));
    std::string function_name = input_args[0];
    try
    {
        nb_rows = std::stoi(input_args[1]);
        nb_cols = std::stoi(input_args[2]);
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("Failed to convert rows or columns to integers: " + std::string(e.what()));
    }

    // the function manager takes care of choosing the right function
    function = std::make_unique<FunctionManager<T>>(function_name);
}

// Destructor
template <typename T>
MatrixGeneratorFromFunction<T>::~MatrixGeneratorFromFunction() {}

// Function to generate the matrix
template <typename T>
MatrixPointer<T> MatrixGeneratorFromFunction<T>::generate_matrix()
{
    std::cout << "Generating Matrix from function..." << std::endl;
    auto matrix = std::make_shared<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>(nb_rows, nb_cols);

    // Populate the matrix using the selected function
    for (int i = 0; i < nb_rows; ++i)
    {
        for (int j = 0; j < nb_cols; ++j)
        {
            (*matrix)(i, j) = (*function)(i, j); // Call the functor with the row and column indices
        }
    }
    return matrix;
}

// Explicit instantiations
template class MatrixGeneratorFromFunction<float>;
template class MatrixGeneratorFromFunction<double>;