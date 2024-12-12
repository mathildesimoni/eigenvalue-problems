#include <iostream>
#include <fstream>
#include <string>

#include "FileReaderCSV.hpp"

template <typename T>
FileReaderCSV<T>::FileReaderCSV(const std::string &fileName) : FileReader<T>(fileName) {} // Calls the parent constructor

template <typename T>
FileReaderCSV<T>::~FileReaderCSV() {}

template <typename T>
MatrixPointer<T> FileReaderCSV<T>::ReadFile()
{
    std::ifstream file(std::string(Paths::PATH_MATRICES).append(this->fileName));
    if (!file.is_open()) // We make sure the file exists, otherwise throw an error
        throw FileException("Failed to open CSV file: " + this->fileName);

    // First, we want to count the number of rows and columns and check there is no inconsistency
    size_t numRows = 0;
    size_t numCols = 0;
    std::string line;
    std::string value;
    while (std::getline(file, line))
    {
        std::istringstream lineStream(line); // This will be used to break the words
        size_t colsInRows = 0;
        while (std::getline(lineStream, value, ','))
            ++colsInRows; // Count the number of values in the current row
        if (numCols == 0)
            numCols = colsInRows; // This is for the first row
        else if (colsInRows != numCols)
            throw FileException("Inconsistent number of columns in CSV file: " + this->fileName);
        numRows++;
    }

    // We do another check to check that the file is not empty
    if (numRows == 0)
        throw FileException("CSV file is empty: " + this->fileName);

    // Now we process with reading the file
    auto matrixPointer = std::make_shared<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>(numRows, numCols);

    file.clear();  // So that we can read the file a second time
    file.seekg(0); // Go back to beginning of file
    size_t rowIdx = 0;

    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        size_t colIdx = 0;

        while (std::getline(lineStream, value, ','))
        {
            try
            {
                if constexpr (std::is_same_v<T, float>)
                    (*matrixPointer)(rowIdx, colIdx) = std::stof(value);
                else if constexpr (std::is_same_v<T, double>)
                    (*matrixPointer)(rowIdx, colIdx) = std::stod(value);
                else
                    throw FileException("Found unsupported element type in CSV file");
                colIdx++;
            }
            catch (const std::exception &e) // Print a better error message (giving context)
            {
                throw FileException("Error parsing the CSV file " + this->fileName + " (" + e.what() + ")");
            }
        }
        rowIdx++;
    }
    file.close();
    return matrixPointer;
}

template class FileReaderCSV<float>;
template class FileReaderCSV<double>;
