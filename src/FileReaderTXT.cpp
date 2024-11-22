#include "FileReaderTXT.hpp"
#include "FileReader.hpp"
#include "constants.hpp"
#include <iostream>
#include <fstream>
#include <string>

template <typename T>
FileReaderTXT<T>::FileReaderTXT(const std::string &file_name) : FileReader<T>(file_name) {} // Calls the parent constructor

template <typename T>
FileReaderTXT<T>::~FileReaderTXT() {}

template <typename T>
std::unique_ptr<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> FileReaderTXT<T>::read_file()
{
    std::cout << "Reading TXT file..." << std::endl;

    std::ifstream file(std::string(Paths::PATH_MATRICES).append(this->file_name));
    if (!file.is_open()) // We make sure the file exists, otherwise throw an error
        throw std::runtime_error("Failed to open TXT file: " + this->file_name);

    // First, we want to count the number of rows and columns and check there is no inconsistency
    size_t num_rows = 0;
    size_t num_cols = 0;
    std::string line;
    std::string value;
    while (std::getline(file, line))
    {
        std::istringstream line_stream(line); // This will be used to break the words
        size_t cols_in_row = 0;
        while (std::getline(line_stream, value, ' '))
            ++cols_in_row; // Count the number of values in the current row
        if (num_cols == 0)
            num_cols = cols_in_row; // This is for the first row
        else if (cols_in_row != num_cols)
            throw std::runtime_error("Inconsistent number of columns in TXT file: " + this->file_name);
        num_rows++;
    }

    // We do another check to check that the file is not empty
    if (num_rows == 0)
        throw std::runtime_error("TXT file is empty: " + this->file_name);

    // Now we process with reading the file
    // We choose to return a unique_pointer for better memory management
    auto matrix_pointer = std::make_unique<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>(num_rows, num_cols);

    file.clear();  // So that we can read the file a second time
    file.seekg(0); // Go back to beginning of file
    size_t row_idx = 0;

    while (std::getline(file, line))
    {
        std::istringstream line_stream(line);
        size_t col_idx = 0;

        while (std::getline(line_stream, value, ' '))
        {
            try
            {
                if constexpr (std::is_same_v<T, float>)
                    (*matrix_pointer)(row_idx, col_idx) = std::stof(value);
                else if constexpr (std::is_same_v<T, double>)
                    (*matrix_pointer)(row_idx, col_idx) = std::stod(value);
                else
                    throw std::runtime_error("Unsupported matrix type");
                col_idx++;
                // TODO: how to make things better?
            }
            catch (const std::exception &e)
            {
                throw std::runtime_error("Error parsing the TXT file " + this->file_name);
            }
        }
        row_idx++;
    }
    file.close();
    return matrix_pointer;
}

template class FileReaderTXT<float>;
template class FileReaderTXT<double>;
