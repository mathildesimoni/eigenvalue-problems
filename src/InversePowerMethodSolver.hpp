
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
    void SetInitialGuess(const Eigen::Matrix<T, -1, 1>); // eigen vector type?
    void SetMatrix(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>);

    virtual void FindEigenvalues(std::ostream &stream);

private:
    Eigen::Matrix<T, -1, 1> initialGuess;
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> matrix;
};


#endif