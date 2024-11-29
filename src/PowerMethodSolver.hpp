
#ifndef POWERMETHODSOLVER_HPP_
#define POWERMETHODSOLVER_HPP_

#include <Eigen/Dense>
#include "AbstractIterativeSolver.hpp"

template <typename T>
class PowerMethodSolver: public AbstractIterativeSolver<T>
{
public: 
    // Constructor and destructor
    PowerMethodSolver();
    virtual ~PowerMethodSolver();

    // Public methods
    void SetShift(const double);

    virtual Vector<T> FindEigenvalues() override;

private:
    double shift;

};

#endif