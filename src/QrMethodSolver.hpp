
#ifndef QRMETHODSOLVER_HPP_
#define QRMETHODSOLVER_HPP_

#include <Eigen/Dense>
#include "AbstractIterativeSolver.hpp"

template <typename T>
class QrMethodSolver: public AbstractIterativeSolver<T>
{
public:
    // Constructor and destructor
    QrMethodSolver();
    virtual ~QrMethodSolver();

    // Public methods
    virtual Vector<T> FindEigenvalues() override;

};

#endif