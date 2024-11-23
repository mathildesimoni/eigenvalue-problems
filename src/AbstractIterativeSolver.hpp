
#ifndef ABSTRACTITERATIVESOLVER_HPP_
#define ABSTRACTITERATIVESOLVER_HPP_

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

    virtual void FindEigenvalues() = 0;

    // Get methods

private:
    int maxIter;
    double tolerance;
};

#endif