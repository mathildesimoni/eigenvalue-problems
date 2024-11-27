
#ifndef POWERMETHODSOLVERSHIFT_HPP_
#define POWERMETHODSOLVERSHIFT_HPP_

#include <Eigen/Dense>
#include "AbstractIterativeSolver.hpp"

template <typename T>
class PowerMethodSolverShift: public AbstractIterativeSolver<T>
{
public: 
    // Constructor and destructor
    PowerMethodSolverShift();
    virtual ~PowerMethodSolverShift();

    // Public methods
    void SetInitialGuess(const Eigen::Matrix<T, -1, 1>); // eigen vector type?
    void SetMatrix(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>);
    void SetShift(const double);
    void SetNRows(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>);
    void SetNColumns(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>);

    virtual void FindEigenvalues(std::ostream &stream);

    // Get methods
    // Eigen::VectorXf GetInitialGuess() const { return initialGuess; }
    // Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> GetMatrix() const { return matrix; }

private:
    Eigen::Matrix<T, -1, 1> initialGuess;
    Eigen::Matrix<T, -1, 1>  matrix;
    double shift;
    int n_rows;
    int n_columns;
};

#endif