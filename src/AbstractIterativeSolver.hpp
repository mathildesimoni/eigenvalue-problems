
#ifndef ABSTRACTITERATIVESOLVER_HPP_
#define ABSTRACTITERATIVESOLVER_HPP_

#include <Eigen/Dense>

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
    void SetMatrix(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> matrix);

    virtual Eigen::Matrix<T, Eigen::Dynamic, 1> FindEigenvalues() = 0;

    // Get methods
    int GetMaxIter() const { return maxIter; }
    double GetTolerance() const { return tolerance; }
    // returns a reference
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& GetMatrix() const { return matrix; }

private:
    int maxIter;
    double tolerance;
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> matrix;
   
};

#endif