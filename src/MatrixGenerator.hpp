
#ifndef __MATRIX_GENERATOR__HH__
#define __MATRIX_GENERATOR__HH__

#include <Eigen/Dense>
#include "constants.hpp"

template <typename T>
class MatrixGenerator
{
public:
    MatrixGenerator() {};
    virtual ~MatrixGenerator() {};
    virtual MatrixPointer<T> generate_matrix() = 0;
};

#endif