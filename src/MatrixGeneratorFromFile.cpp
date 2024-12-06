#include "MatrixGeneratorFromFile.hpp"
#include <iostream>
#include "FileReaderCSV.hpp"
#include "FileReaderTXT.hpp"
#include "FileReaderMTX.hpp"

// Function to generate the matrix
template <typename T>
MatrixPointer<T> MatrixGeneratorFromFile<T>::generate_matrix()
{
    std::cout << "Generating Matrix from file..." << std::endl;
    if (!file_reader)
    {
        throw std::runtime_error("File reader not initialized");
    } // TODO: handle this
    return file_reader->read_file();
}

// Explicit instantiations
template class MatrixGeneratorFromFile<float>;
template class MatrixGeneratorFromFile<double>;