
#ifndef __ABSTRACT_ITERATIVE_SOLVER_HPP__
#define __ABSTRACT_ITERATIVE_SOLVER_HPP__

#include <Eigen/Dense>
#include "constants.hpp"

/**
 * \brief Abstract base class for solving an eigenvalue problem
 *
 * Derived classes should implement the `FindEigenvalues` method;
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class AbstractIterativeSolver
{
public:
    // Constructor and desctructor
    AbstractIterativeSolver(double tolerance, int maxIter) : tolerance(tolerance), maxIter(maxIter) {};
    virtual ~AbstractIterativeSolver();

    // Public methods
    void SetMatrix(MatrixPointer<T> matrix);
    virtual Vector<T> FindEigenvalues() = 0;

    // Get methods
    int GetMaxIter() const { return maxIter; }
    double GetTolerance() const { return tolerance; }
    MatrixPointer<T> GetMatrix() const;

private:
    int maxIter;
    double tolerance;
    MatrixPointer<T> matrix_pointer;
};

#endif