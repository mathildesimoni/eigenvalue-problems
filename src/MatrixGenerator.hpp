
#ifndef __MATRIX_GENERATOR__HH__
#define __MATRIX_GENERATOR__HH__

#include <Eigen/Dense>

template <typename T>
class MatrixGenerator
{
public:
    MatrixGenerator() {};
    virtual ~MatrixGenerator() {};
    virtual std::unique_ptr<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> generate_matrix() = 0;
};

#endif