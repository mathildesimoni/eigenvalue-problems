#include <iostream>

#include "InversePowerMethodSolver.hpp"

template <typename T>
InversePowerMethodSolver<T>::InversePowerMethodSolver(double tolerance, int maxIter, double shift)
    : AbstractIterativeSolver<T>(tolerance, maxIter), shift(shift) {}

template <typename T>
InversePowerMethodSolver<T>::~InversePowerMethodSolver() {}

template <typename T>
Vector<T> InversePowerMethodSolver<T>::FindEigenvalues()
{

    // Get parameters from abstract class
    double tolerance = this->GetTolerance();
    int maxIter = this->GetMaxIter();
    double error = tolerance + 1.0;
    int iterCount = 0;

    MatrixPointer<T> A_ptr = this->GetMatrix();
    Matrix<T> A_shifted = *A_ptr - shift * Matrix<T>::Identity((*A_ptr).rows(), (*A_ptr).cols());

    // Declare initial guess
    Vector<T> x_ini = Vector<T>::Ones(A_shifted.rows());

    T lambdaOld = (x_ini.transpose() * (A_shifted * x_ini)).value() / (x_ini.transpose() * x_ini).value();
    T lambdaNew;

    while (error > tolerance && iterCount < maxIter)
    {
        Vector<T> x_new = A_shifted.colPivHouseholderQr().solve(x_ini);
        Vector<T> solverError = (A_shifted * x_new) - x_ini;

        if (solverError.norm() > 1e16)
                throw std::runtime_error("No solution: matrix is too badly conditioned. This method is unsuitable for eigenvalue computation in such cases.");

        // Compute eigenvalue lambda using Rayleigh quotient
        lambdaNew = (x_new.transpose() * (A_shifted * x_new)).value() / (x_new.transpose() * x_new).value();

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
    // std::cout << "Total number of iterations: " << iterCount << std::endl;

    Vector<T> result(1);
    result(0) = lambdaNew + shift;
    return result;
}

// Explicit instantation
template class InversePowerMethodSolver<float>;
template class InversePowerMethodSolver<double>;