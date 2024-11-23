
#ifndef ABSTRACTITERATIVESOLVER_HPP_
#define ABSTRACTITERATIVESOLVER_HPP_

// #include <Eigen/Dense>

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

    virtual void FindEigenvalues(std::ostream &stream) = 0;

    // Get methods
    int GetMaxIter() const { return maxIter; }
    double GetTolerance() const { return tolerance; }

private:
    int maxIter;
    double tolerance;
   
};

#endif