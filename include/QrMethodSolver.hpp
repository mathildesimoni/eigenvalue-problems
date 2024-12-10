
#ifndef __QR_METHOD_SOLVER_HPP__
#define __QR_METHOD_SOLVER_HPP__

#include <Eigen/Dense>
#include "AbstractIterativeSolver.hpp"

/**
 * \brief Class for finding an eigenvalue using the QR algorithm.
 *
 * This class extends the AbstractIterativeSolver base class by providing a method that 
 * finds all eigenvalues of a matrix, using an iterative algorithm base on QR decomposition.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class QrMethodSolver : public AbstractIterativeSolver<T>
{
public:
    // Constructor and destructor
    QrMethodSolver(double tolerance, int maxIter);
    ~QrMethodSolver();

    // Public methods
    /**
     * \brief Performs the QR decomposition of A using the Householder transformation.
     * Q and R are modified in-place.
     */
    void QrDecomposition(const Matrix<T>& A_iter, Matrix<T>& Q, Matrix<T>& R);

    /**
     * \brief Finds the Eigenvalues of the matrix stored in matrix_pointer using the QR algorithm.
     * \return An Eigen vector of length equal to the number of row of the matrix containing the 
     * eigenvalues found by the method.
     */
    Vector<T> FindEigenvalues() override;
};

#endif