
#ifndef __INVERSE_POWER_METHOD_SOLVER_HPP__
#define __INVERSE_POWER_METHOD_SOLVER_HPP__

#include <Eigen/Dense>
#include "AbstractIterativeSolver.hpp"

template <typename T>
class InversePowerMethodSolver : public AbstractIterativeSolver<T>
{
public:
    // Constructor and destructor
    InversePowerMethodSolver();
    ~InversePowerMethodSolver();

    // public methods
    // void SetInitialGuess(const Eigen::Matrix<T, -1, 1>); // eigen vector type?
    void SetShift(const double);

    Vector<T> FindEigenvalues() override;

private:
    // Eigen::Matrix<T, -1, 1> initialGuess;
    double shift;
};

#endif