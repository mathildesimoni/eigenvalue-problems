#include <iostream>
#include <fstream>
#include <string>

#include "FileReaderMTX.hpp"

template <typename T>
FileReaderMTX<T>::FileReaderMTX(const std::string &fileName) : FileReader<T>(fileName) {} // Calls the parent constructor

template <typename T>
FileReaderMTX<T>::~FileReaderMTX() {}

template <typename T>
MatrixPointer<T> FileReaderMTX<T>::ReadFile()
{
    std::ifstream file(std::string(Paths::PATH_MATRICES).append(this->fileName));
    if (!file.is_open()) // We make sure the file exists, otherwise throw an error
        throw FileException("Failed to open MTX file: " + this->fileName);

    size_t numRows = 0;
    size_t numCols = 0;
    std::string line;
    T value;

    // First we skip the headers
    std::getline(file, line);
    while (line.find("%") == 0)
        std::getline(file, line);

    // Then, we want to find the number of rows and columns
    std::istringstream dimStream(line);
    dimStream >> numRows >> numCols;

    // We do another check to check that the file is not empty
    if (numRows == 0 || numCols == 0)
        throw FileException("MTX file is empty: " + this->fileName);

    // Now we process with reading the file
    // We choose to return a unique_pointer for better memory management
    auto matrixPointer = std::make_shared<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>(numRows, numCols);
    matrixPointer->setZero(); // Initialize matrix with zeros!

    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        size_t rowIdx;
        size_t colIdx;

        try
        {
            lineStream >> rowIdx >> colIdx >> value;
            if (lineStream.fail()) // If reading fails, throw an exception
            {
                throw FileException("Invalid value encountered in MTX file: " + this->fileName + " (line: " + line + ")");
            }
        }
        catch (const std::exception &e)
        {
            throw FileException("Error parsing value in MTX file: " + this->fileName + " (" + e.what() + ")");
        }

        rowIdx--; // Go to 0-based indexing in cpp
        colIdx--;

        if (rowIdx < 0 || rowIdx >= numRows || colIdx < 0 || colIdx >= numCols)
            throw FileException("Invalid indices in MTX file: " + this->fileName);
        (*matrixPointer)(rowIdx, colIdx) = value;
    }

    file.close();
    return matrixPointer;
}

template class FileReaderMTX<float>;
template class FileReaderMTX<double>;
