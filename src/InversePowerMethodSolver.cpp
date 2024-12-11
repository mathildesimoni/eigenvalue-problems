#include <iostream>
#include "InversePowerMethodSolver.hpp"
#include "AbstractIterativeSolver.hpp"

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
    int max_iter = this->GetMaxIter();
    double error = tolerance + 1.0;
    int iter_count = 0;

    MatrixPointer<T> A_ptr = this->GetMatrix();
    Matrix<T> A_shifted = *A_ptr - shift * Matrix<T>::Identity((*A_ptr).rows(), (*A_ptr).cols());

    // declare initial guess
    Vector<T> x_ini = Vector<T>::Ones(A_shifted.rows());

    T lambda_old = (x_ini.transpose() * (A_shifted * x_ini)).value() / (x_ini.transpose() * x_ini).value();
    T lambda_new;

    std::cout << "tolerance: " << tolerance << std::endl;
    std::cout << "maxIter: " << max_iter << std::endl;
    std::cout << "initial error: " << error << std::endl;

    while (error > tolerance && iter_count < max_iter)
    {
        Vector<T> x_new = A_shifted.colPivHouseholderQr().solve(x_ini);

        // compute eigenvalue lambda using Rayleigh quotient
        lambda_new = (x_new.transpose() * (A_shifted * x_new)).value() / (x_new.transpose() * x_new).value();

        // compute error as abs(lambda_old - lambda_new)
        error = std::abs(lambda_new - lambda_old) / std::abs(lambda_new);

        // Increment iteration count, and update values of x and lambda
        lambda_old = lambda_new;
        x_ini = x_new;
        ++iter_count;
    }

    if (iter_count >= max_iter)
    {
        std::cerr << "[WARNING] Maximum number of iterations reached.\n"
                  << "          Consider using a higher number for the maximum number of iterations."
                  << std::endl;
    }
    std::cout << "Total number of iterations: " << iter_count << std::endl;

    Vector<T> result(1);
    result(0) = lambda_new + shift;
    return result;
}

// Explicit instantation
template class InversePowerMethodSolver<float>;
template class InversePowerMethodSolver<double>;