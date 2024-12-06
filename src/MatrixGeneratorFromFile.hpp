
#ifndef __MATRIX_GENERATOR_FROM_FILE__HH__
#define __MATRIX_GENERATOR_FROM_FILE__HH__

#include <Eigen/Dense>
#include "MatrixGenerator.hpp"
#include "FileReader.hpp"

/**
 * \brief Class for generating matrices from files.
 *
 * This class extends the MatrixGenerator base class and uses a FileReader
 * to load matrix data from various file formats such as CSV, TXT, and MTX.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class MatrixGeneratorFromFile : public MatrixGenerator<T>
{
public:
    MatrixGeneratorFromFile(std::unique_ptr<FileReader<T>> file_reader) : file_reader(std::move(file_reader)) {}; /**< Constructor */
    ~MatrixGeneratorFromFile() {};                                                                                /**< Destructor */
    /**
     * \brief Generates a matrix from the specified file.
     *
     * \return A shared pointer to an Eigen matrix of type T containing the generated data.
     */
    MatrixPointer<T> generate_matrix() override;

private:
    std::unique_ptr<FileReader<T>> file_reader; /**< A pointer to the FileReader used for reading the matrix. */
};

#endif