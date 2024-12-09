
#ifndef __MATRIX_GENERATOR__HH__
#define __MATRIX_GENERATOR__HH__

#include <Eigen/Dense>
#include "constants.hpp"

/**
 * \brief Abstract base class for generating matrices.
 *
 * Derived classes should implement the `generate_matrix` method to create
 * matrices using specified user input
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class MatrixGenerator
{
public:
    MatrixGenerator() {};          /**< Constructor */
    virtual ~MatrixGenerator() {}; /**< Destructor */
    /**
     * \brief Pure virtual function to generate a matrix.
     *
     * Derived classes must implement this method to provide specific matrix generation functionality.
     *
     * \return A shared pointer to an Eigen matrix of type T.
     */
    virtual MatrixPointer<T> generate_matrix() = 0;
};

#endif