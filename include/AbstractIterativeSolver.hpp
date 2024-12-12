
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
    AbstractIterativeSolver(double tolerance, int maxIter) : tolerance(tolerance), maxIter(maxIter) {}; /**< Constructor */
    virtual ~AbstractIterativeSolver();                                                                 /**< Destructor */

    // Public methods
    void SetMatrix(MatrixPointer<T> matrix);
    /**
     * \brief Pure virtual function to find the eigenvalues of the matrix associated to the instance of the class.
     *
     * This method must be overridden in derived classes
     *
     * \return A pointer to an Eigen vector containing the eigenvalues.
     * This vector has a different size depending on the solver method.
     */
    virtual Vector<T> FindEigenvalues() = 0;

    // Get methods
    int GetMaxIter() const { return maxIter; }
    double GetTolerance() const { return tolerance; }
    MatrixPointer<T> GetMatrix() const;

private:
    int maxIter;                    /**< Maximum number of iteration in the iterative method */
    double tolerance;               /**< Tolerance to stop the iterative method */
    MatrixPointer<T> matrixPointer; /**< Pointer to the matrix to find eigenvalues of */
};

/**
 * \brief Class to handle solver-related errors.
 *
 * This class is derived from `std::exception` and is used to represent
 * errors specifically related to the solvers
 */
class SolverException : public std::exception
{
    std::string message; /**< Custom error message */

public:
    SolverException(const std::string &msg) : message(msg) {} /**< Constructor */
    /// Retrieve the error message
    const char *what() const throw()
    {
        return message.c_str();
    }
};

#endif