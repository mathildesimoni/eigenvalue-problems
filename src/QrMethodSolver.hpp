
#ifndef __QR_METHOD_SOLVER_HPP__
#define __QR_METHOD_SOLVER_HPP__

#include <Eigen/Dense>
#include "AbstractIterativeSolver.hpp"

template <typename T>
class QrMethodSolver : public AbstractIterativeSolver<T>
{
public:
    // Constructor and destructor
    QrMethodSolver();
    ~QrMethodSolver();

    // Public methods
    Vector<T> FindEigenvalues() override;
    void QrDecomposition(const Matrix<T>& A_shifted, Matrix<T>& Q, Matrix<T>& R);
};

#endif