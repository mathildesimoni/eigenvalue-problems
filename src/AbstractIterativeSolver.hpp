
#ifndef ABSTRACTITERATIVESOLVER_HPP_
#define ABSTRACTITERATIVESOLVER_HPP_

#include <Eigen/Dense>
#include <memory>
#include "constants.hpp"

template <typename T>
class AbstractIterativeSolver
{
public:
    // constructor and desctructor
    AbstractIterativeSolver();
    virtual ~AbstractIterativeSolver();

    // public methods
    void SetMaxIter(const int maxIter);
    void SetTolerance(const double tolerance);
    void SetMatrix(MatrixPointer<T> matrix);

    virtual Vector<T> FindEigenvalues() = 0;

    // Get methods
    int GetMaxIter() const { return maxIter; }
    double GetTolerance() const { return tolerance; }
    // returns a reference
    MatrixPointer<T> GetMatrix() const; // const { return matrix_pointer; }
    // const MatrixPointer<T> GetMatrix() const { return matrix_pointer; }

private:
    int maxIter;
    double tolerance;
    MatrixPointer<T> matrix_pointer;
   
};

#endif