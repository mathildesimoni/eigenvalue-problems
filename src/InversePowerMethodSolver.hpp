
#ifndef INVERSEPOWERMETHODSOLVER_HPP_
#define INVERSEPOWERMETHODSOLVER_HPP_

#include <Eigen/Dense>
#include "AbstractIterativeSolver.hpp"

template <typename T>
class InversePowerMethodSolver: public AbstractIterativeSolver<T>
{
public:
    // Constructor and destructor
    InversePowerMethodSolver();
    virtual ~InversePowerMethodSolver();

    // public methods
    // void SetInitialGuess(const Eigen::Matrix<T, -1, 1>); // eigen vector type?
    void SetShift(const double);

    virtual Vector<T> FindEigenvalues() override;

private:
    // Eigen::Matrix<T, -1, 1> initialGuess;
    double shift;
};


#endif