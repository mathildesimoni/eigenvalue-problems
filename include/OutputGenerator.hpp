#ifndef __OUTPUT_GENERATOR__HH__
#define __OUTPUT_GENERATOR__HH__

#include <iostream>
#include <functional>
#include <Eigen/Dense>
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
    OutputGenerator(const std::string &outputType, const std::vector<std::string> &outputArgs, Vector<T> &data); /**< Constructor */
    ~OutputGenerator() {};                                                                                       /**< Destructor */
    void GenerateOutput();                                                                                       /**< Executes the selected output mechanism.*/
    void WriteInFile();                                                                                          /**< Saves eigenvalues to a file.*/
    void PrintToTerminal();                                                                                      /**< Prints eigenvalues to the terminal.*/

private:
    std::vector<std::string> outputArgs;  /**< Arguments related to the output (e.g. file name for "save"). */
    std::function<void()> outputFunction; /**< The selected output function (e.g. printing or file saving). */
    Vector<T> eigenvalues;                /**< The vector of eigenvalues to output. */
};

#endif