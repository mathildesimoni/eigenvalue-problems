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
void AbstractIterativeSolver<T>::SetMatrix(const Matrix<T>& matrix)
{ 
    assert (matrix.rows() && matrix.cols());
    matrix_pointer = &matrix; 
}

// template <typename T>
// const Matrix<T>& AbstractIterativeSolver<T>::GetMatrix() const { return *matrix_pointer; }
// check nrows_ncolumns

// Explicit instantiation
template class AbstractIterativeSolver<float>;
template class AbstractIterativeSolver<double>;