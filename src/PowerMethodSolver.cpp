#include <iostream>
#include "PowerMethodSolver.hpp"
#include "AbstractIterativeSolver.hpp"

template <typename T>
PowerMethodSolver<T>::PowerMethodSolver() {}

template <typename T>
PowerMethodSolver<T>::~PowerMethodSolver() {}

template <typename T>
void PowerMethodSolver<T>::SetInitialGuess(const Eigen::Vector<T, Eigen::Dynamic> x_0){ initialGuess=x_O; }

template <typename T>
void PowerMethodSolver<T>::SetMatrix(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A){ matrix=A; }
// add assertions if needed for that particular solver

template <typename T>
void PowerMethodSolver<T>::FindEigenvalues(std::ostream &stream) {

    // Get parameters from parent abstract class 
    double tolerance = GetTolerance();

    int max_iter = GetMaxIter();

    double error = tolerance + 1.0;
    int iter_count = 0;

    x_ini = initialGuess;
    x_ini.normalize();

    double lambda_old = 0.0;
    double lambda_new = 0.0;

    // Retrieve pointer to matrix
    // (auto& deduces the type of the variable and binds it to a reference: no copies)
    const auto& A_ptr = GetMatrix();
    // A is a reference to the dereferenced object: not a copy of it
    // because it is a constant we cannot modify A
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& A = *A_ptr;

    while (error > tolerance && iter_count < max_iter) {
        // Multiply A * x_0
        Eigen::VectorXf Ax = A * x_ini;

        // compute norm of solution
        double norm = Ax.norm();

        // divide by the norm and update x_new
        x_new = Ax / norm;

        // compute eigenvalue lambda using Rayleigh quotient
        lambda_new = x_new.dot(A * x_new);

        // compute error as abs(lambda_old - lambda_new)
        error = std::abs(lambda_new - lambda_old);

        // Increment iteration count, and update values of x and lambda
        lambda_old = lambda_new;
        x_ini = x_new;
        ++iter_count;

    // print out dominant eigenvalue (last lambda_new)
    std::cout << "Dominant eigenvalue: " << lambda_new << std::endl;
    if (iter_count >= max_iter) {
        std::cout << "Warning: maximum number of iterations reached." << std::endl;
    }

    // ?? Add warning message if we reached max number of iteration instead of convergence??

    }
}

// Explicit instantation
template class PowerMethodSolver<float>;
template class PowerMethodSolver<double>;
