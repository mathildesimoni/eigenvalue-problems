
#ifndef INVERSEPOWERMETHODSOLVER_HPP_
#define INVERSEPOWERMETHODSOLVER_HPP_

#include <Eigen/Dense>
#include "AbstractIterativeSolver.hpp"

template <typename T>
class InversePowerMethodSolverShift: public AbstractIterativeSolver<T>
{
public:
    // Constructor and destructor
    InversePowerMethodSolverShift();
    virtual ~InversePowerMethodSolverShift();

    // public methods
    void SetInitialGuess(const Eigen::Matrix<T, -1, 1>); // eigen vector type?
    void SetMatrix(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>);
    void SetShift(const double);
    void SetNRows(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>);
    void SetNColumns(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>);

    virtual void FindEigenvalues(std::ostream &stream);

private:
    Eigen::Matrix<T, -1, 1> initialGuess;
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> matrix;
    double shift;
    int n_rows;
    int n_columns;
};

#endif