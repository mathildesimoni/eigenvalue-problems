#include "MatrixGeneratorFromFunction.hpp"
#include "MatrixGeneratorFromFile.hpp"
#include "FileReaderCSV.hpp"
#include "FileReaderTXT.hpp"
#include "FileReaderMTX.hpp"
#include "FileReader.hpp"
#include "MatrixGeneratorFactory.hpp"
#include <stdexcept>

template <typename T>
std::unique_ptr<MatrixGenerator<T>> MatrixGeneratorFactory<T>::choose_generator()
{
    if (input_name == "function")
    {
        return choose_function_generator();
    }
    else if (input_name == "file")
    {
        return choose_file_generator();
    }
    else
    {
        throw std::runtime_error(input_name + " is a supported input type but is not linked to a valid implementation.\n"
                                              "Consider updating the MatrixGeneratorFactory to consider this input type");
    }
}

template <typename T>
std::unique_ptr<MatrixGenerator<T>> MatrixGeneratorFactory<T>::choose_file_generator()
{
    // Check that the vector of arguments has exactly one argument, otherwise throw an error
    if (input_args.size() != 1)
        throw std::invalid_argument("Expected exactly one argument (file name), but got " + std::to_string(input_args.size()));
    std::string file_name = input_args[0];

    // Find file extension
    auto pos = file_name.find_last_of('.');
    if (pos == std::string::npos)
    {
        throw std::invalid_argument("File name has no extension: " + file_name);
    }
    std::string extension = file_name.substr(pos + 1);

    std::unique_ptr<FileReader<T>> file_reader;
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
    return std::make_unique<MatrixGeneratorFromFile<T>>(std::move(file_reader));
}

template <typename T>
std::unique_ptr<MatrixGenerator<T>> MatrixGeneratorFactory<T>::choose_function_generator()
{
    // Check that the vector has exactly 3 argument, otherwise throw an error and cast the last 2 to ints
    if (input_args.size() != 3)
        throw std::invalid_argument("Expected exactly 3 arguments (function name, number of rows, number of columns), but got " + std::to_string(input_args.size()));
    std::string function_name = input_args[0];
    int nb_rows;
    int nb_cols;
    try
    {
        nb_rows = std::stoi(input_args[1]);
        nb_cols = std::stoi(input_args[2]);
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("Failed to convert rows or columns to integers: " + std::string(e.what()));
    }

    if (function_name == "identity" || function_name == "hilbert")
    {
        auto function = std::make_unique<FunctionManager<T>>(function_name);
        return std::make_unique<MatrixGeneratorFromFunction<T>>(std::move(function), nb_rows, nb_cols);
    }
    else
    {
        throw std::invalid_argument("Unknown function name: " + function_name);
    }
}

// Explicit instantiations
template class MatrixGeneratorFactory<double>;
template class MatrixGeneratorFactory<float>;