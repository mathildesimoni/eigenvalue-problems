#include <iostream>
#include "PowerMethodSolverShift.hpp"
#include "AbstractIterativeSolver.hpp"

template <typename T>
PowerMethodSolverShift<T>::PowerMethodSolverShift() {}

template <typename T>
PowerMethodSolverShift<T>::~PowerMethodSolverShift() {}

template <typename T>
void PowerMethodSolverShift<T>::SetInitialGuess(const Eigen::Matrix<T, -1, 1>   x_0){ initialGuess=x_0; }

template <typename T>
void PowerMethodSolverShift<T>::SetMatrix(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A){ matrix=A; }
// add assertions if needed for that particular solver

template <typename T>
void PowerMethodSolverShift<T>::SetShift(const double mu){ shift=mu; }

template <typename T>
void PowerMethodSolverShift<T>::SetNRows(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A){
    // Count number of rows and columns of matrix A
    n_rows = matrix.rows();
}

template <typename T>
void PowerMethodSolverShift<T>::SetNColumns(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A){
    // Count number of rows and columns of matrix A
    n_columns = matrix.cols();
}

template <typename T>
void PowerMethodSolverShift<T>::FindEigenvalues(std::ostream &stream) {

    // Get parameters from parent abstract class 
    double tolerance = this->GetTolerance();

    int max_iter = this->GetMaxIter();

    double error = tolerance + 1.0;
    int iter_count = 0;

    Eigen::Matrix<T, -1, 1> x_ini = initialGuess;
    x_ini.normalize();

    // Retrieve pointer to matrix
    // (auto& deduces the type of the variable and binds it to a reference: no copies)
    const auto& A_ptr = AbstractIterativeSolver<T>::GetMatrix();
    // A is a reference to the dereferenced object: not a copy of it
    // because it is a constant we cannot modify A

    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& A = *A_ptr;
    // Compute shifted version of the matrix
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A_shifted = A - mu * Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Identity(n_rows, n_columns);
    
    double lambda_old = x_ini.dot(A * x_ini);
    double lambda_new;

    while (error > tolerance && iter_count < max_iter) {
        // Multiply A * x_0
        Eigen::Matrix<T, -1, 1> x_new = A_shifted * x_ini;

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
    std::cout << "Dominant eigenvalue: " << lambda_new << std::endl;
    if (iter_count >= max_iter) {
        std::cout << "Warning: maximum number of iterations reached." << std::endl;
    }

}

// Explicit instantation
template class PowerMethodSolverShift<float>;
template class PowerMethodSolverShift<double>;
