#include <iostream>
#include <fstream>
#include <string>

#include "FileReaderTXT.hpp"

template <typename T>
FileReaderTXT<T>::FileReaderTXT(const std::string &fileName) : FileReader<T>(fileName) {} // Calls the parent constructor

template <typename T>
FileReaderTXT<T>::~FileReaderTXT() {}

template <typename T>
MatrixPointer<T> FileReaderTXT<T>::ReadFile()
{
    std::ifstream file(std::string(Paths::PATH_MATRICES).append(this->fileName));
    if (!file.is_open()) // We make sure the file exists, otherwise throw an error
        throw std::runtime_error("Failed to open TXT file: " + this->fileName);

    // First, we want to count the number of rows and columns and check there is no inconsistency
    size_t numRows = 0;
    size_t numCols = 0;
    std::string line;
    std::string value;
    while (std::getline(file, line))
    {
        std::istringstream lineStream(line); // This will be used to break the words
        size_t colsInRow = 0;
        while (std::getline(lineStream, value, ' '))
            ++colsInRow; // Count the number of values in the current row
        if (numCols == 0)
            numCols = colsInRow; // This is for the first row
        else if (colsInRow != numCols)
            throw std::runtime_error("Inconsistent number of columns in TXT file: " + this->fileName);
        numRows++;
    }

    // We do another check to check that the file is not empty
    if (numRows == 0)
        throw std::runtime_error("TXT file is empty: " + this->fileName);

    // Now we process with reading the file
    // We choose to return a unique_pointer for better memory management
    auto matrixPointer = std::make_shared<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>(numRows, numCols);

    file.clear();  // So that we can read the file a second time
    file.seekg(0); // Go back to beginning of file
    size_t rowIdx = 0;

    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        size_t colIdx = 0;

        while (std::getline(lineStream, value, ' '))
        {
            try
            {
                if constexpr (std::is_same_v<T, float>)
                    (*matrixPointer)(rowIdx, colIdx) = std::stof(value);
                else if constexpr (std::is_same_v<T, double>)
                    (*matrixPointer)(rowIdx, colIdx) = std::stod(value);
                else
                    throw std::runtime_error("Found unsupported element type in TXT file");
                colIdx++;
            }
            catch (const std::exception &e)
            {
                throw std::runtime_error("Error parsing the TXT file " + this->fileName);
            }
        }
        rowIdx++;
    }
    file.close();
    return matrixPointer;
}

template class FileReaderTXT<float>;
template class FileReaderTXT<double>;
