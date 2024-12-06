
#ifndef __POWER_METHOD_SOLVER_HPP__
#define __POWER_METHOD_SOLVER_HPP__

#include <Eigen/Dense>
#include "AbstractIterativeSolver.hpp"

template <typename T>
class PowerMethodSolver : public AbstractIterativeSolver<T>
{
public:
    // Constructor and destructor
    PowerMethodSolver();
    ~PowerMethodSolver();

    // Public methods
    void SetShift(const double);

    Vector<T> FindEigenvalues() override;

private:
    double shift;
};

#endif