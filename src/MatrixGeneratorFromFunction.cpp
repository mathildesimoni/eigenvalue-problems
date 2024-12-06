#include "MatrixGeneratorFromFunction.hpp"
#include "FunctionManager.hpp"
#include <iostream>

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