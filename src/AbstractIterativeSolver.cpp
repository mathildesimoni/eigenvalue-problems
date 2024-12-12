#include <iostream>

#include "AbstractIterativeSolver.hpp"

template <typename T>
AbstractIterativeSolver<T>::~AbstractIterativeSolver() {}

template <typename T>
void AbstractIterativeSolver<T>::SetMatrix(MatrixPointer<T> matrix)
{
    if ((*matrix).rows() != (*matrix).cols())
    {
        throw std::invalid_argument("The provided matrix must be square. Rows and columns are not equal.");
    }
    matrixPointer = matrix;
}

template <typename T>
MatrixPointer<T> AbstractIterativeSolver<T>::GetMatrix() const
{
    // Check that the pointer was assigned to a matrix
    if (matrixPointer == nullptr)
    {
        throw std::runtime_error("Matrix is not initialized (AbstractIterativeSolver)");
    }
    return matrixPointer;
}

// Explicit instantiations
template class AbstractIterativeSolver<float>;
template class AbstractIterativeSolver<double>;