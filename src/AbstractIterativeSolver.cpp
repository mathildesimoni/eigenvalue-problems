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
void AbstractIterativeSolver<T>::SetMatrix(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A){ matrix=A; }
// check nrows_ncolumns

// Explicit instantiation
template class AbstractIterativeSolver<float>;
template class AbstractIterativeSolver<double>;