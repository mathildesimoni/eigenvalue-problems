#include <iostream>

#include "PowerMethodSolver.hpp"

template <typename T>
PowerMethodSolver<T>::PowerMethodSolver(double tolerance, int maxIter, double shift)
    : AbstractIterativeSolver<T>(tolerance, maxIter), shift(shift) {}

template <typename T>
PowerMethodSolver<T>::~PowerMethodSolver() {}

template <typename T>
Vector<T> PowerMethodSolver<T>::FindEigenvalues()
{

    // Get parameters from parent abstract class
    double tolerance = this->GetTolerance();
    int maxIter = this->GetMaxIter();
    double error = tolerance + 1.0;
    int iterCount = 0;

    // Retrieve pointer to matrix
    MatrixPointer<T> A_ptr = this->GetMatrix();
    const Matrix<T> A_shifted = *A_ptr - shift * Matrix<T>::Identity((*A_ptr).rows(), (*A_ptr).cols());

    Vector<T> x_ini = Vector<T>::Ones(A_shifted.rows());
    x_ini.normalize();

    // Declare eigenvalue related to initial guess
    T lambdaOld = x_ini.dot(A_shifted * x_ini);
    T lambdaNew;

    while (error > tolerance && iterCount < maxIter)
    {
        // Multiply A * x_0
        Vector<T> x_new = A_shifted * x_ini;

        // Normalize x_new inplace
        x_new.normalize();

        // Compute eigenvalue lambda using Rayleigh quotient
        lambdaNew = x_new.dot(A_shifted * x_new);

        // Compute error as abs(lambdaOld - lambdaNew)
        error = std::abs(lambdaNew - lambdaOld) / std::abs(lambdaNew);

        // Increment iteration count, and update values of x and lambda
        lambdaOld = lambdaNew;
        x_ini = x_new;
        ++iterCount;
    }

    if (iterCount >= maxIter)
    {
        std::cerr << "[WARNING] Maximum number of iterations reached.\n"
                  << "          Consider using a higher number for the maximum number of iterations."
                  << std::endl;
    }
    std::cout << "Total number of iterations: " << iterCount << std::endl;

    Vector<T> result(1);
    result(0) = lambdaNew + shift;
    return result;
}

// Explicit instantation
template class PowerMethodSolver<float>;
template class PowerMethodSolver<double>;
