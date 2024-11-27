#include <iostream>
#include "PowerMethodSolver.hpp"
#include "AbstractIterativeSolver.hpp"

template <typename T>
PowerMethodSolver<T>::PowerMethodSolver() {}

template <typename T>
PowerMethodSolver<T>::~PowerMethodSolver() {}

template <typename T>
void PowerMethodSolver<T>::SetInitialGuess(const Eigen::Matrix<T, -1, 1>  x_0){ initialGuess=x_0; }

template <typename T>
void PowerMethodSolver<T>::SetShift(const double mu){ shift=mu; }

template <typename T>
void PowerMethodSolver<T>::FindEigenvalues() {

    // Get parameters from parent abstract class 
    double tolerance = this->GetTolerance();

    int max_iter = this->GetMaxIter();

    double error = tolerance + 1.0;
    int iter_count = 0;

    Eigen::Matrix<T, -1, 1> x_ini = initialGuess;
    x_ini.normalize();


    // Retrieve pointer to matrix
    // (auto& deduces the type of the variable and binds it to a reference: no copies)
    // A is a reference to the dereferenced object: not a copy of it
    // because it is a constant we cannot modify A
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& A = this->GetMatrix();
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A_shifted = A - shift * Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Identity(A.rows(), A.cols());
    
    // Declare eigenvalue related to initial guess
    double lambda_old = x_ini.dot(A * x_ini);
    double lambda_new;

    while (error > tolerance && iter_count < max_iter) {
        // Multiply A * x_0
        Eigen::Matrix<T, -1, 1> x_new = A * x_ini;

        // normalize x_new inplace
        x_new.normalize();

        // compute eigenvalue lambda using Rayleigh quotient
        lambda_new = x_new.dot(A * x_new);

        // compute error as abs(lambda_old - lambda_new)
        error = std::abs(lambda_new - lambda_old);

        // Increment iteration count, and update values of x and lambda
        lambda_old = lambda_new;
        x_ini = x_new;
        ++iter_count;
    }

    // print out dominant eigenvalue (last lambda_new)
    std::cout << "Dominant eigenvalue: " << lambda_new << std::endl;
    if (iter_count >= max_iter) {
        std::cout << "Warning: maximum number of iterations reached." << std::endl;

    }
}

// Explicit instantation
template class PowerMethodSolver<float>;
template class PowerMethodSolver<double>;
