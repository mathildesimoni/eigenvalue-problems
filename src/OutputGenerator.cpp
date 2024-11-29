#include "OutputGenerator.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "constants.hpp"

template <typename T>
OutputGenerator<T>::OutputGenerator(const std::string &output_type, const std::string &arg, Eigen::Matrix<T, Eigen::Dynamic, 1> &data)
{
    if (output_type == "print")
    {
        output_function = [this]()
        { return OutputGenerator::print_to_terminal(); };
    }
    else // checks of the choice of output_type were already done when parsing user input
    {
        // Find file extension
        auto pos = arg.find_last_of('.');
        if (pos == std::string::npos)
        {
            throw std::invalid_argument("File name has no extension: " + arg);
        } // TODO: will have to handle this error in main
        std::string extension = arg.substr(pos + 1);
        if (extension != "txt") // we only consider txt files
        {
            throw std::invalid_argument("Unsupported file extension: " + extension);
        }

        output_function = [this]()
        { return OutputGenerator::write_in_file(); };

        output_arg = arg;
    }

    eigenvalues = data;
}

template <typename T>
void OutputGenerator<T>::generate_output()
{
    output_function();
}

template <typename T>
void OutputGenerator<T>::write_in_file()
{
    std::cout << "Saving data to file..." << std::endl;
    std::ofstream out_file(std::string(Paths::PATH_OUTPUT_FILE).append(output_arg));
    if (!out_file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + output_arg);
    }

    for (const auto &eigenvalue : eigenvalues)
    {
        out_file << eigenvalue << "\n";
    }

    out_file.close();
}

template <typename T>
void OutputGenerator<T>::print_to_terminal()
{
    std::cout << "Printing data to terminal..." << std::endl;
    std::cout << "Eigenvalues:" << std::endl;
    for (const auto &eigenvalue : eigenvalues)
        std::cout << eigenvalue << std::endl;
}

// Explicit instantiations
template class OutputGenerator<float>;
template class OutputGenerator<double>;