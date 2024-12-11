#include "MatrixGeneratorFromFile.hpp"
#include <iostream>
#include "FileReaderCSV.hpp"
#include "FileReaderTXT.hpp"
#include "FileReaderMTX.hpp"

// Function to generate the matrix
template <typename T>
MatrixPointer<T> MatrixGeneratorFromFile<T>::GenerateMatrix()
{
    std::cout << "Generating Matrix from file..." << std::endl;
    if (!fileReader)
    {
        throw std::runtime_error("File reader not initialized");
    }
    return fileReader->ReadFile();
}

// Explicit instantiations
template class MatrixGeneratorFromFile<float>;
template class MatrixGeneratorFromFile<double>;