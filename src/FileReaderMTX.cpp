#include "FileReaderMTX.hpp"
#include "FileReader.hpp"
#include "constants.hpp"
#include <iostream>
#include <fstream>
#include <string>

template <typename T>
FileReaderMTX<T>::FileReaderMTX(const std::string &file_name) : FileReader<T>(file_name) {} // Calls the parent constructor

template <typename T>
FileReaderMTX<T>::~FileReaderMTX() {}

template <typename T>
MatrixPointer<T> FileReaderMTX<T>::read_file()
{
    std::cout << "Reading MTX file..." << std::endl;

    std::ifstream file(std::string(Paths::PATH_MATRICES).append(this->file_name));
    if (!file.is_open()) // We make sure the file exists, otherwise throw an error
        throw std::runtime_error("Failed to open MTX file: " + this->file_name);

    size_t num_rows = 0;
    size_t num_cols = 0;
    std::string line;
    T value;

    // First we skip the headers
    std::getline(file, line);
    while (line.find("%") == 0)
        std::getline(file, line);

    // Then, we want to find the number of rows and columns
    std::istringstream dim_stream(line);
    dim_stream >> num_rows >> num_cols;

    // We do another check to check that the file is not empty
    if (num_rows == 0 || num_cols == 0)
        throw std::runtime_error("MTX file is empty: " + this->file_name);

    // Now we process with reading the file
    // We choose to return a unique_pointer for better memory management
    auto matrix_pointer = std::make_shared<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>(num_rows, num_cols);
    matrix_pointer->setZero(); // Initialize matrix with zeros!

    while (std::getline(file, line))
    {
        std::istringstream line_stream(line);
        size_t row_idx;
        size_t col_idx;

        try
        {
            line_stream >> row_idx >> col_idx >> value;
            if (line_stream.fail()) // If reading fails, throw an exception
            {
                throw std::runtime_error("Invalid value encountered in MTX file: " + this->file_name + " (line: " + line + ")");
            }
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error parsing value in MTX file: " + this->file_name + " (" + e.what() + ")");
        }

        // line_stream >> row_idx >> col_idx >> value;
        row_idx--; // Go to 0-based indexing in cpp
        col_idx--;

        if (row_idx < 0 || row_idx >= num_rows || col_idx < 0 || col_idx >= num_cols)
            throw std::runtime_error("Invalid indices in MTX file: " + this->file_name);
        (*matrix_pointer)(row_idx, col_idx) = value;
    }

    file.close();
    return matrix_pointer;
}

template class FileReaderMTX<float>;
template class FileReaderMTX<double>;
