#include <iostream>
#include "PowerMethodSolver.hpp"
#include "AbstractIterativeSolver.hpp"

template <typename T>
PowerMethodSolver<T>::PowerMethodSolver() {}

template <typename T>
PowerMethodSolver<T>::~PowerMethodSolver() {}

template <typename T>
void PowerMethodSolver<T>::SetShift(const double mu) { shift = mu; }

template <typename T>
Vector<T> PowerMethodSolver<T>::FindEigenvalues()
{

    // Get parameters from parent abstract class
    double tolerance = this->GetTolerance();
    int max_iter = this->GetMaxIter();
    double error = tolerance + 1.0;
    int iter_count = 0;

    // Retrieve pointer to matrix
    // (auto& deduces the type of the variable and binds it to a reference: no copies)
    // A is a reference to the dereferenced object: not a copy of it
    // because it is a constant we cannot modify A
    MatrixPointer<T> A_ptr = this->GetMatrix();
    const Matrix<T> A_shifted = *A_ptr - shift * Matrix<T>::Identity((*A_ptr).rows(), (*A_ptr).cols());

    Vector<T> x_ini = Vector<T>::Ones(A_shifted.rows());
    x_ini.normalize();

    // Declare eigenvalue related to initial guess
    T lambda_old = x_ini.dot(A_shifted * x_ini);
    T lambda_new;

    while (error > tolerance && iter_count < max_iter)
    {
        // Multiply A * x_0
        Vector<T> x_new = A_shifted * x_ini;

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
    // std::cout << "Dominant eigenvalue: " << lambda_new << std::endl;
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
template class PowerMethodSolver<float>;
template class PowerMethodSolver<double>;
