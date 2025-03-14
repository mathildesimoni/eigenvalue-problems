
#ifndef __MATRIX_GENERATOR__HH__
#define __MATRIX_GENERATOR__HH__

#include "constants.hpp"

/**
 * \brief Abstract base class for generating matrices.
 *
 * Derived classes should implement the `GenerateMatrix()` method to create
 * matrices using specified user input
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class MatrixGenerator
{
public:
    /// Constructor
    MatrixGenerator() {};
    /// Destructor
    virtual ~MatrixGenerator() {};
    /**
     * \brief Pure virtual function to generate a matrix.
     *
     * Derived classes must implement this method to provide specific matrix generation functionality.
     *
     * \return A shared pointer to an Eigen matrix of type T.
     */
    virtual MatrixPointer<T> GenerateMatrix() = 0;
};

#endif