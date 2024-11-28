
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
    // void SetInitialGuess(const Eigen::Matrix<T, -1, 1>); // eigen vector type?
    void SetShift(const double);

    virtual Eigen::Matrix<T, Eigen::Dynamic, 1> FindEigenvalues() override;

private:
    // Eigen::Matrix<T, -1, 1> initialGuess;
    // Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> matrix;
    double shift;

};

#endif