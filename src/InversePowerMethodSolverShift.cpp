#include <iostream>
#include "InversePowerMethodSolverShift.hpp"
#include "AbstractIterativeSolver.hpp"

template <typename T>
InversePowerMethodSolverShift<T>::InversePowerMethodSolverShift() {}

template <typename T>
InversePowerMethodSolverShift<T>::~InversePowerMethodSolverShift() {}

template <typename T>
void InversePowerMethodSolverShift<T>::SetInitialGuess(const Eigen::Matrix<T, -1, 1> x_0){ initialGuess=x_0; }

template <typename T>
void InversePowerMethodSolverShift<T>::SetMatrix(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A){ matrix=A; }

template <typename T>
void InversePowerMethodSolverShift<T>::SetShift(const double mu){ shift=mu; }

template <typename T>
void InversePowerMethodSolverShift<T>::SetNRows(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A){
    // Count number of rows and columns of matrix A
    n_rows = matrix.rows();
}

template <typename T>
void InversePowerMethodSolverShift<T>::SetNColumns(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A){
    // Count number of rows and columns of matrix A
    n_columns = matrix.cols();
}

template <typename T>
void InversePowerMethodSolverShift<T>::FindEigenvalues(std::ostream &stream) {

    // Get parameters from parent abstract class 
    double tolerance = this->GetTolerance();

    int max_iter = this->GetMaxIter();

    double error = tolerance + 1.0;
    int iter_count = 0;

    Eigen::Matrix<T, -1, 1> x_ini = initialGuess;
    x_ini.normalize();


    // Retrieve pointer to matrix
    // (auto& deduces the type of the variable and binds it to a reference: no copies)
    const auto& A_ptr = GetMatrix();
    // A is a reference to the dereferenced object: not a copy of it
    // because it is a constant we cannot modify A
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A = *A_ptr;
    // Compute shifted version of the matrix
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A_shifted = A - mu * Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Identity(n_rows, n_columns);

    double lambda_old = x_ini.dot(A * x_ini);
    double lambda_new;

    while (error > tolerance && iter_count < max_iter) {
       // solve the linear system to find next eigenvector iteration
        Eigen::Matrix<T, -1, 1> x_new = A_shifted.colPivHouseholderQr().solve(x_ini);

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
template class InversePowerMethodSolverShift<float>;
template class InversePowerMethodSolverShift<double>;