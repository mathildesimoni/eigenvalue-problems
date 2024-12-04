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
    OutputGenerator(const std::string &output_type, const std::vector<std::string> &output_args, Vector<T> &data); /**< Constructor */
    ~OutputGenerator() {};                                                                                         /**< Destructor */
    void generate_output();                                                                                        /**< Executes the selected output mechanism.*/
    void write_in_file();                                                                                          /**< Saves eigenvalues to a file.*/
    void print_to_terminal();                                                                                      /**< Prints eigenvalues to the terminal.*/

private:
    std::vector<std::string> output_args;  /**< Arguments related to the output (e.g. file name for "save"). */
    std::function<void()> output_function; /**< The selected output function (e.g. printing or file saving). */
    Vector<T> eigenvalues;                 /**< The vector of eigenvalues to output. */
};

#endif