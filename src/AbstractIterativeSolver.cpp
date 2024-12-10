#include <iostream>
#include "AbstractIterativeSolver.hpp"

// template <typename T>
// AbstractIterativeSolver<T>::AbstractIterativeSolver()
//     : maxIter(), tolerance() {}

template <typename T>
AbstractIterativeSolver<T>::~AbstractIterativeSolver() {}

// template <typename T>
// void AbstractIterativeSolver<T>::SetMaxIter(const int max_iter) { maxIter = max_iter; }

// template <typename T>
// void AbstractIterativeSolver<T>::SetTolerance(const double tol) { tolerance = tol; }

template <typename T>
void AbstractIterativeSolver<T>::SetMatrix(MatrixPointer<T> matrix)
{
    // TODO: remove
    std::cout << "nrows: " << (*matrix).rows() << std::endl;
    std::cout << "ncols: " << (*matrix).cols() << std::endl;

    if ((*matrix).rows() != (*matrix).cols())
    {
        throw std::invalid_argument("Matrix must be square. Rows and columns are not equal.");
    }
    // assert((*matrix).rows() == (*matrix).cols());
    matrix_pointer = matrix;
    // const MatrixPointer<T> matrix_pointer = matrix;
    std::cout << "matrix in setting method " << matrix << std::endl;
    std::cout << "matrix_pointer in setting method " << matrix_pointer << std::endl;
}

template <typename T>
MatrixPointer<T> AbstractIterativeSolver<T>::GetMatrix() const
{
    // Check that the pointer was assigned to a matrix
    if (matrix_pointer == nullptr)
    {
        throw std::runtime_error("Matrix is not initialized!");
    }
    return matrix_pointer;
}

// Explicit instantiation
template class AbstractIterativeSolver<float>;
template class AbstractIterativeSolver<double>;