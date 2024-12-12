#include <iostream>

#include "MatrixGeneratorFromFile.hpp"
#include "FileReaderCSV.hpp"
#include "FileReaderTXT.hpp"
#include "FileReaderMTX.hpp"

// Function to generate the matrix
template <typename T>
MatrixPointer<T> MatrixGeneratorFromFile<T>::GenerateMatrix()
{
    if (!fileReader)
    {
        throw std::runtime_error("File reader not initialized (in MatrixGeneratorFromFile)");
    }
    return fileReader->ReadFile();
}

// Explicit instantiations
template class MatrixGeneratorFromFile<float>;
template class MatrixGeneratorFromFile<double>;