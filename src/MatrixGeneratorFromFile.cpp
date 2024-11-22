#include "MatrixGeneratorFromFile.hpp"
#include <iostream>
#include "FileReaderCSV.hpp"
#include "FileReaderTXT.hpp"
#include "FileReaderMTX.hpp"

// Constructor
template <typename T>
MatrixGeneratorFromFile<T>::MatrixGeneratorFromFile(const std::string &file_name)
{
    // Find file extension
    auto pos = file_name.find_last_of('.');
    if (pos == std::string::npos)
    {
        throw std::invalid_argument("File name has no extension: " + file_name);
    } // TODO: will have to handle this error in main
    std::string extension = file_name.substr(pos + 1);

    // Instantiate the correct file reader
    if (extension == "csv")
    {
        file_reader = std::make_unique<FileReaderCSV<T>>(file_name);
    }
    else if (extension == "txt")
    {
        file_reader = std::make_unique<FileReaderTXT<T>>(file_name);
    }
    else if (extension == "mtx")
    {
        file_reader = std::make_unique<FileReaderMTX<T>>(file_name);
    }
    else
    {
        throw std::invalid_argument("Unsupported file extension: " + extension);
    }
}

// Destructor
template <typename T>
MatrixGeneratorFromFile<T>::~MatrixGeneratorFromFile() {}

// Function to generate the matrix
template <typename T>
std::unique_ptr<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> MatrixGeneratorFromFile<T>::generate_matrix()
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