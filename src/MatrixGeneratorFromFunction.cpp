#include <iostream>

#include "MatrixGeneratorFromFunction.hpp"
#include "FunctionManager.hpp"

// Function to generate the matrix
template <typename T>
MatrixPointer<T> MatrixGeneratorFromFunction<T>::GenerateMatrix()
{
    auto matrix = std::make_shared<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>(nbRows, nbCols);

    // Populate the matrix using the selected function
    for (int i = 0; i < nbRows; ++i)
    {
        for (int j = 0; j < nbCols; ++j)
        {
            (*matrix)(i, j) = (*function)(i, j); // Call the functor with the row and column indices
        }
    }
    return matrix;
}

// Explicit instantiations
template class MatrixGeneratorFromFunction<float>;
template class MatrixGeneratorFromFunction<double>;