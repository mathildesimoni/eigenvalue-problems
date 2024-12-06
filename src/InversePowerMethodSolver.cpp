#include <iostream>
#include "InversePowerMethodSolver.hpp"
#include "AbstractIterativeSolver.hpp"

template <typename T>
InversePowerMethodSolver<T>::InversePowerMethodSolver() {}

template <typename T>
InversePowerMethodSolver<T>::~InversePowerMethodSolver() {}

// template <typename T>
// void InversePowerMethodSolver<T>::SetInitialGuess(const Eigen::Matrix<T, -1, 1> x_0) { initialGuess = x_0; }

template <typename T>
void InversePowerMethodSolver<T>::SetShift(const double mu) { shift = mu; }

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
    // TODO: add random x_ini based on user input
    Vector<T> x_ini = Vector<T>::Ones(A_shifted.rows());
    // x_ini.normalize();

    T lambda_old = x_ini.dot(A_shifted * x_ini);
    T lambda_new;

    while (error > tolerance && iter_count < max_iter)
    {
        // solve the linear system to find next eigenvector iteration
        // TODO: choose solver or dynamic based on user input
        Vector<T> x_new = A_shifted.colPivHouseholderQr().solve(x_ini);
        // Vector x_new = A_shifted.template bdcSvd<Eigen::ComputeThinU | Eigen::ComputeThinV>().solve(x_ini);

        // normalize x_new inplace
        x_new.normalize();

        // compute eigenvalue lambda using Rayleigh quotient
        lambda_new = x_new.dot(A_shifted * x_new);

        // compute error as abs(lambda_old - lambda_new)
        error = std::abs(lambda_new - lambda_old);

        // Increment iteration count, and update values of x and lambda
        lambda_old = lambda_new;
        x_ini = x_new;
        ++iter_count;
    }

    // print out dominant eigenvalue (last lambda_new)
    if (iter_count >= max_iter)
    {
        std::cerr << "[WARNING] Maximum number of iterations reached.\n"
                  << "          Consider using a higher number for the maximum number of iterations."
                  << std::endl;
    }
    std::cout << "Total number of iterations: " << iter_count << std::endl;

    Vector<T> result(1);
    result(0) = lambda_new;
    return result;
}

// Explicit instantation
template class InversePowerMethodSolver<float>;
template class InversePowerMethodSolver<double>;