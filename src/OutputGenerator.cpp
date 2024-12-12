#include <iostream>
#include <string>
#include <fstream>

#include "OutputGenerator.hpp"
#include "FileReader.hpp"

template <typename T>
OutputGenerator<T>::OutputGenerator(const std::string &outputType, const std::vector<std::string> &args, Vector<T> &data)
{
    eigenvalues = data;

    if (outputType == "print")
    {
        outputFunction = [this]()
        { return OutputGenerator::PrintToTerminal(); };
    }
    else if (outputType == "save")
    {
        try
        {
            std::string filename = args[0];
            auto pos = filename.find_last_of('.'); // Find file extension
            if (pos == std::string::npos)
                throw std::invalid_argument("File name has no extension: " + filename + ") during output generation");
            std::string extension = filename.substr(pos + 1);
            if (extension != "txt")
                throw std::invalid_argument("Unsupported file extension: " + extension + ") during output generation");
            outputFunction = [this]()
            { return OutputGenerator::WriteInFile(); };
            outputArgs = args;
        }
        // Catch the error by saving to a specified default file
        catch (const std::exception &e)
        {
            std::cerr << "[WARNING] Error processing the output filename during output generation: " << e.what() << std::endl
                      << "          Handling the issue by saving the output to " << DefaultOutputArgs::FILENAME
                      << std::endl;
            outputFunction = [this]()
            { return OutputGenerator::WriteInFile(); };
            outputArgs = std::vector<std::string>{DefaultOutputArgs::FILENAME};
        }
    }
    else
    {
        throw std::runtime_error(outputType + " is a supported output type but is not linked to a valid implementation.\n"
                                              "Consider updating OutputGenerator to consider this output type");
    }
}

template <typename T>
void OutputGenerator<T>::GenerateOutput()
{
    outputFunction();
}

template <typename T>
void OutputGenerator<T>::WriteInFile()
{
    std::cout << "Saving data to file..." << std::endl;
    std::ofstream outFile(std::string(Paths::PATH_OUTPUT_FILE).append(outputArgs[0]));
    if (!outFile.is_open())
    {
        throw FileException("Failed to open file " + outputArgs[0] + " when generating output");
    }

    for (const auto &eigenvalue : eigenvalues)
    {
        outFile << eigenvalue << "\n";
    }

    outFile.close();
}

template <typename T>
void OutputGenerator<T>::PrintToTerminal()
{
    std::cout << "Eigenvalues:" << std::endl;
    for (const auto &eigenvalue : eigenvalues)
        std::cout << eigenvalue << std::endl;
}

// Explicit instantiations
template class OutputGenerator<float>;
template class OutputGenerator<double>;