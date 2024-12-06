#include "OutputGenerator.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "constants.hpp"

template <typename T>
OutputGenerator<T>::OutputGenerator(const std::string &output_type, const std::vector<std::string> &args, Vector<T> &data)
{
    eigenvalues = data;

    if (output_type == "print")
    {
        output_function = [this]()
        { return OutputGenerator::print_to_terminal(); };
    }
    else if (output_type == "save")
    {
        try
        {
            std::string filename = args[0];
            auto pos = filename.find_last_of('.'); // Find file extension
            if (pos == std::string::npos)
                throw std::invalid_argument("File name has no extension: " + filename);
            std::string extension = filename.substr(pos + 1);
            if (extension != "txt")
                throw std::invalid_argument("Unsupported file extension: " + extension);
            output_function = [this]()
            { return OutputGenerator::write_in_file(); };
            output_args = args;
        }
        // Catch the error by saving to a specified file
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cerr << "Handling the issue by saving the output to output.txt!" << std::endl;
            output_function = [this]()
            { return OutputGenerator::write_in_file(); };
            output_args = std::vector<std::string>{"output.txt"};
        }
    }
    else
    {
        throw std::runtime_error(output_type + " is a supported output type but is not linked to a valid implementation.\n"
                                               "Consider updating OutputGenerator to consider this output type");
    }
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
    std::ofstream out_file(std::string(Paths::PATH_OUTPUT_FILE).append(output_args[0]));
    if (!out_file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + output_args[0]);
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
    std::cout << "Eigenvalues:" << std::endl;
    for (const auto &eigenvalue : eigenvalues)
        std::cout << eigenvalue << std::endl;
}

// Explicit instantiations
template class OutputGenerator<float>;
template class OutputGenerator<double>;