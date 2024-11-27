
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
    void SetInitialGuess(const Eigen::Matrix<T, -1, 1>); // eigen vector type?
    void SetMatrix(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>);

    virtual void FindEigenvalues(std::ostream &stream);

    // Get methods
    // Eigen::VectorXf GetInitialGuess() const { return initialGuess; }
    // Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> GetMatrix() const { return matrix; }

private:
    Eigen::Matrix<T, -1, 1> initialGuess;
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> matrix;
};

#endif