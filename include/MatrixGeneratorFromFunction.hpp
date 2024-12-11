
#ifndef __MATRIX_GENERATOR_FROM_FUNCTION__HH__
#define __MATRIX_GENERATOR_FROM_FUNCTION__HH__

#include <Eigen/Dense>
#include "MatrixGenerator.hpp"
#include "FunctionManager.hpp"

/**
 * \brief Class for generating matrices using mathematical functions.
 *
 * This class extends the MatrixGenerator base class and uses a function provided
 * by FunctionManager to populate the matrix elements.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class MatrixGeneratorFromFunction : public MatrixGenerator<T>
{
public:
    MatrixGeneratorFromFunction(std::unique_ptr<FunctionManager<T>> function, int nbRows, int nbCols) : function(std::move(function)), nbRows(nbRows), nbCols(nbCols) {}; /**< Constructor */
    ~MatrixGeneratorFromFunction() {};                                                                                                                                    /**< Destructor */
    /**
     * \brief Generates a matrix using the specified function.
     *
     * \return A shared pointer to an Eigen matrix of type T containing the generated data.
     */
    MatrixPointer<T> GenerateMatrix() override;

private:
    int nbRows;                                   /**< The number of rows in the generated matrix. */
    int nbCols;                                   /**< The number of columns in the generated matrix. */
    std::unique_ptr<FunctionManager<T>> function; /**< A function manager to provide the matrix generation function. */
};

#endif