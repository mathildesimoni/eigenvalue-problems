#ifndef __OUTPUT_GENERATOR__HH__
#define __OUTPUT_GENERATOR__HH__

#include <iostream>
#include <functional>

#include "constants.hpp"

/**
 * \brief Class for generating outputs of eigenvalue computations.
 *
 * This class handles the output of eigenvalue results either by printing them
 * to the terminal or saving them to a file, based on user-specified options.
 *
 * \tparam T The data type of the eigenvalues (e.g. float, double).
 */
template <typename T>
class OutputGenerator
{
public:
    /// Constructor
    OutputGenerator(const std::string &outputType, const std::vector<std::string> &outputArgs, Vector<T> &data);
    /// Destructor
    ~OutputGenerator() {};
    /// Method to execute the selected output mechanism
    void GenerateOutput();
    /// Method to save eigenvalues to a file
    void WriteInFile();
    /// Method to print eigenvalues to terminal
    void PrintToTerminal();

private:
    std::vector<std::string> outputArgs;  /**< Arguments related to the output (e.g. file name for "save"). */
    std::function<void()> outputFunction; /**< The selected output function (e.g. printing or file saving). */
    Vector<T> eigenvalues;                /**< The vector of eigenvalues to output. */
};

#endif