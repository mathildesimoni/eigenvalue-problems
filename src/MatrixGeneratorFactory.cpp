#include "MatrixGeneratorFactory.hpp"
#include "FileReaderCSV.hpp"
#include "FileReaderTXT.hpp"
#include "FileReaderMTX.hpp"

template <typename T>
std::unique_ptr<MatrixGenerator<T>> MatrixGeneratorFactory<T>::ChooseGenerator()
{
    if (inputName == "function")
    {
        return ChooseFunctionGenerator();
    }
    else if (inputName == "file")
    {
        return ChooseFileGenerator();
    }
    else
    {
        throw std::runtime_error(inputName + " is a supported input type but is not linked to a valid implementation.\n"
                                             "Consider updating the MatrixGeneratorFactory to consider this input type");
    }
}

template <typename T>
std::unique_ptr<MatrixGeneratorFromFile<T>> MatrixGeneratorFactory<T>::ChooseFileGenerator()
{
    // Check that the vector of arguments has exactly one argument, otherwise throw an error
    if (inputArgs.size() != 1)
        throw std::invalid_argument("Expected exactly one argument for matrix initialization (file name), but got " + std::to_string(inputArgs.size()));
    std::string fileName = inputArgs[0];

    // Find file extension
    auto pos = fileName.find_last_of('.');
    if (pos == std::string::npos)
    {
        throw std::invalid_argument("File name has no extension (" + fileName + ") during matrix initialization");
    }
    std::string extension = fileName.substr(pos + 1);

    std::unique_ptr<FileReader<T>> fileReader;
    // Instantiate the correct file reader
    if (extension == "csv")
    {
        fileReader = std::make_unique<FileReaderCSV<T>>(fileName);
    }
    else if (extension == "txt")
    {
        fileReader = std::make_unique<FileReaderTXT<T>>(fileName);
    }
    else if (extension == "mtx")
    {
        fileReader = std::make_unique<FileReaderMTX<T>>(fileName);
    }
    else
    {
        throw std::invalid_argument("Unsupported file extension (" + extension + ") during matrix initialization");
    }
    return std::make_unique<MatrixGeneratorFromFile<T>>(std::move(fileReader));
}

template <typename T>
std::unique_ptr<MatrixGeneratorFromFunction<T>> MatrixGeneratorFactory<T>::ChooseFunctionGenerator()
{
    // Check that the vector has exactly 3 argument, otherwise throw an error and cast the last 2 to ints
    if (inputArgs.size() != 3)
        throw std::invalid_argument("Expected exactly 3 arguments for matrix initialization (function name, number of rows, number of columns), but got " + std::to_string(inputArgs.size()));
    std::string functionName = inputArgs[0];
    int nbRows;
    int nbCols;
    try
    {
        nbRows = std::stoi(inputArgs[1]);
        nbCols = std::stoi(inputArgs[2]);
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("Failed to convert rows or columns to integers during matrix initialization: " + std::string(e.what()));
    }

    if (functionName == "identity" || functionName == "hilbert")
    {
        auto function = std::make_unique<FunctionManager<T>>(functionName);
        return std::make_unique<MatrixGeneratorFromFunction<T>>(std::move(function), nbRows, nbCols);
    }
    else
    {
        throw std::invalid_argument("Unknown function name (" + functionName + ") during matrix initialization");
    }
}

// Explicit instantiations
template class MatrixGeneratorFactory<double>;
template class MatrixGeneratorFactory<float>;