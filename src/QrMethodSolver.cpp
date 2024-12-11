#include <iostream>
#include "QrMethodSolver.hpp"
#include "AbstractIterativeSolver.hpp"

template <typename T>
QrMethodSolver<T>::QrMethodSolver(double tolerance, int maxIter) : AbstractIterativeSolver<T>(tolerance, maxIter) {}

template <typename T>
QrMethodSolver<T>::~QrMethodSolver() {}

template <typename T>
void QrMethodSolver<T>::QrDecomposition(const Matrix<T> &A_iter, Matrix<T> &Q, Matrix<T> &R)
{
    // A_shifted is passed as a const so that it can not be modified

    int n = A_iter.rows(); // Number of rows (same as number of columns)

    // Initialize Q and R
    Q = Matrix<T>::Identity(n, n);
    R = A_iter;

    for (int k = 0; k < n; k++)
    {

        Vector<T> x = R.block(k, k, n - k, 1);
        Vector<T> v = x;
        v(0) += (x.norm() * (x(0) >= 0 ? 1 : -1)); // v = x + sign(x_0) * ||x|| * e_1

        v = v / v.norm(); // Normalize the vector v

        // Apply Householder transformation to the trailing matrix
        R.block(k, k, n - k, n - k) -= 2 * v * v.transpose() * R.block(k, k, n - k, n - k);

        // Apply Householder transformation to Q
        Q.block(0, k, n, n - k) -= 2 * Q.block(0, k, n, n - k) * v * v.transpose();
    }
}

template <typename T>
Vector<T> QrMethodSolver<T>::FindEigenvalues()
{

    // Get parameters from parent abstract class
    double tolerance = this->GetTolerance();
    int maxIter = this->GetMaxIter();
    double error = tolerance + 1.0;
    int iterCount = 0;

    // Retrieve pointer to matrix
    MatrixPointer<T> A_ptr = this->GetMatrix();
    Matrix<T> A_iter = *A_ptr;
    int n = A_iter.rows();

    // Initialize Q and R
    Matrix<T> Q(n, n);
    Matrix<T> R(n, n);

    while (error > tolerance && iterCount < maxIter)
    {
        // Perform QR decomposition
        QrDecomposition(A_iter, Q, R);

        // Compute next iterate
        A_iter = R * Q;

        // Compute the error as the sum of the absolute below-diagonal elements
        error = 0.0;
        for (int i = 1; i < A_iter.rows(); ++i)
        {
            for (int j = 0; j < i; ++j)
            { // Below-diagonal entries
                error += std::abs(A_iter(i, j));
            }
        }

        // Increment iteration count
        ++iterCount;
    }
    if (iterCount >= maxIter)
    {
        std::cerr << "[WARNING] Maximum number of iterations reached.\n"
                  << "          Consider using a higher number for the maximum number of iterations."
                  << std::endl;
    }
    std::cout << "Total number of iterations: " << iterCount << std::endl;
    return A_iter.diagonal();
}

// Explicit instantiation
template class QrMethodSolver<float>;
template class QrMethodSolver<double>;