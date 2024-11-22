
#ifndef __MATRIX_GENERATOR_FROM_FUNCTION__HH__
#define __MATRIX_GENERATOR_FROM_FUNCTION__HH__

#include <Eigen/Dense>
#include "MatrixGenerator.hpp"
#include "FunctionManager.hpp"

template <typename T>
class MatrixGeneratorFromFunction : public MatrixGenerator<T>
{
public:
    MatrixGeneratorFromFunction(const std::vector<std::string> &input_args);
    std::unique_ptr<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> generate_matrix() override;
    ~MatrixGeneratorFromFunction();

private:
    int nb_rows;
    int nb_cols;
    std::unique_ptr<FunctionManager<T>> function;
};

#endif