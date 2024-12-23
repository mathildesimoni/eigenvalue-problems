
#ifndef __POWER_METHOD_SOLVER_HPP__
#define __POWER_METHOD_SOLVER_HPP__

#include "AbstractIterativeSolver.hpp"

/**
 * \brief Class for finding an eigenvalue using the Power method.
 *
 * This class extends the AbstractIterativeSolver base class by providing the
 * power solver method (with a shift to be chosen) to find the eigenvalue of a matrix.
 *
 * The eigenvalue found by this method is the dominant eigenvalue. By choosing
 * a value for the shift, the convergence of the method may be increased.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class PowerMethodSolver : public AbstractIterativeSolver<T>
{
public:
    /// Constructor
    PowerMethodSolver(double tolerance, int maxIter, double shift);
    /// Destructor
    ~PowerMethodSolver();

    // Public methods
    /**
     * \brief Finds the Eigenvalue of the matrix stored in matrixPointer using the power method.
     * \return An Eigen vector of size (1) containing the eigenvalue found by the method.
     */
    Vector<T> FindEigenvalues() override;

private:
    double shift; /**< Optional shift */
};

#endif