
#ifndef __INVERSE_POWER_METHOD_SOLVER_HPP__
#define __INVERSE_POWER_METHOD_SOLVER_HPP__

#include <Eigen/Dense>
#include "AbstractIterativeSolver.hpp"

/**
 * \brief Class for finding an eigenvalue using the Inverse Power method.
 *
 * This class extends the AbstractIterativeSolver base class by providing the inverse 
 * power solver method (with a shift to be chosen) to find the eigenvalue of a matrix.
 * 
 * When no shift is specified, this methods finds the smallest eigenvalue of the matrix.
 * Otherwise, it finds the eigenvalue closest to the shift value.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class InversePowerMethodSolver : public AbstractIterativeSolver<T>
{
public:
    // Constructor and destructor
    InversePowerMethodSolver(double tolerance, int maxIter, double shift);
    ~InversePowerMethodSolver();

    // public methods
    // void SetInitialGuess(const Eigen::Matrix<T, -1, 1>); // eigen vector type?
    void SetShift(const double);
    /**
     * \brief Finds the Eigenvalue of the matrix stored in matrix_pointer using the inverse power method.
     * \return An Eigen vector of size (1) containing the eigenvalue found by the method.
     */
    Vector<T> FindEigenvalues() override;

private:
    // Eigen::Matrix<T, -1, 1> initialGuess;
    double shift;
};

#endif