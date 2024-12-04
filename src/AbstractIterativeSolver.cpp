#include <iostream>
#include "AbstractIterativeSolver.hpp"

template <typename T>
AbstractIterativeSolver<T>::AbstractIterativeSolver()
    : maxIter(), tolerance() {}

template <typename T>
AbstractIterativeSolver<T>::~AbstractIterativeSolver() {}

template <typename T>
void AbstractIterativeSolver<T>::SetMaxIter(const int max_iter){ maxIter = max_iter; }

template <typename T>
void AbstractIterativeSolver<T>::SetTolerance(const double tol){ tolerance=tol; }

template <typename T>
void AbstractIterativeSolver<T>::SetMatrix(MatrixPointer<T> matrix)
{ 
    std::cout << "nrows: " << (*matrix).rows() << std::endl;
    std::cout << "ncols: " << (*matrix).cols() << std::endl;

    assert ((*matrix).rows() == (*matrix).cols());
    matrix_pointer = matrix;
    // const MatrixPointer<T> matrix_pointer = matrix;
    std::cout << "matrix in setting method " << matrix << std::endl;
    std::cout << "matrix_pointer in setting method " << matrix_pointer << std::endl;
}

template <typename T>
MatrixPointer<T> AbstractIterativeSolver<T>::GetMatrix() const {
    if (!matrix_pointer) {
        std::cerr << "Matrix is not initialized!" << std::endl;
    }
    return matrix_pointer;
}

// Explicit instantiation
template class AbstractIterativeSolver<float>;
template class AbstractIterativeSolver<double>;