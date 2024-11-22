
#ifndef __MATRIX_GENERATOR_FROM_FILE__HH__
#define __MATRIX_GENERATOR_FROM_FILE__HH__

#include <Eigen/Dense>
#include "MatrixGenerator.hpp"
#include "FileReader.hpp"

template <typename T>
class MatrixGeneratorFromFile : public MatrixGenerator<T>
{
public:
    MatrixGeneratorFromFile(const std::vector<std::string> &input_args);
    std::unique_ptr<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> generate_matrix() override;
    ~MatrixGeneratorFromFile();

private:
    std::unique_ptr<FileReader<T>> file_reader;
};

#endif