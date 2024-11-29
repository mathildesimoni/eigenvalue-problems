#include <iostream>
#include "QrMethodSolver.hpp"
#include "AbstractIterativeSolver.hpp"

template <typename T>
QrMethodSolver<T>::QrMethodSolver() {}

template <typename T>
QrMethodSolver<T>::~QrMethodSolver() {}

template <typename T>
Vector<T> QrMethodSolver<T>::FindEigenvalues() {

    // Get parameters from parent abstract class 
    double tolerance = this->GetTolerance();
    int max_iter = this->GetMaxIter();
    double error = tolerance + 1.0;
    int iter_count = 0;

    // Retrieve pointer to matrix
   const Matrix<T>& A_ptr = this->GetMatrix();
    // try "eigen matrix copy constructor"
    Matrix<T> A_iter = A_ptr;

    while (error > tolerance && iter_count < max_iter) {
        // Perform QR decomposition
        Eigen::HouseholderQR<Matrix<T>> qr(A_iter);
        Matrix<T> Q = qr.householderQ();
        Matrix<T> R = qr.matrixQR().template triangularView<Eigen::Upper>();

        // Compute next iterate
        A_iter = R * Q;

        // Compute the error as the sum of the absolute below-diagonal elements
        error = 0.0;
        for (int i = 1; i < A_iter.rows(); ++i) {
            for (int j = 0; j < i; ++j) { // Below-diagonal entries
                error += std::abs(A_iter(i, j));
            }
        }

        // Increment iteration count
        ++iter_count;
    }
    if (iter_count >= max_iter) {
        std::cout << "Warning: maximum number of iterations reached." << std::endl;
    }
    std::cout << "Total number of iterations: " << iter_count << std::endl;
    return A_iter.diagonal();
}

// Explicit instantiation
template class QrMethodSolver<float>;
template class QrMethodSolver<double>;