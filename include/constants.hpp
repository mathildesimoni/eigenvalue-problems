#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

#include <set>
#include <string>

#include <Eigen/Dense>

/**
 * \brief Type alias to represent the type of matrix element (float or double).
 *
 * Enables to handle different types in the main.py file
 */
using MatrixVariant = std::variant<float, double>;

template <typename T>
using MatrixPointer = std::shared_ptr<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>;

template <typename T>
using Matrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

template <typename T>
using Vector = Eigen::Matrix<T, Eigen::Dynamic, 1>;

/**
 * \brief Namespace for file path constants.
 *
 * This namespace contains constants that define the paths used for input
 * and output files in the application.
 */
namespace Paths
{
    // These paths are relative to the build/ folder where the executables are
    const std::string PATH_INPUT_FILE = "../input/";
    const std::string PATH_MATRICES = "../input/matrices/";
    const std::string PATH_OUTPUT_FILE = "../output/";
}

/**
 * \brief Namespace for supported argument constants.
 *
 * This namespace defines constants for supported input types, matrix types,
 * methods, and output actions, which provides a way to manage supported
 * configurations.
 */
namespace SupportedArguments
{
    /// Supported types for matrix elements
    const std::set<std::string> SUPPORTED_TYPES = {
        "int",
        "float",
        "double"};

    /// Supported methods
    const std::set<std::string> SUPPORTED_METHODS = {
        "power_method",
        "inverse_power_method",
        "QR_method"};

    /// Supported input types
    const std::set<std::string> SUPPORTED_INPUT_TYPES = {
        "file",
        "function"};

    /// Supported output actions
    const std::set<std::string> SUPPORTED_OUTPUT_TYPES = {
        "print",
        "save"};
}

/**
 * \brief Namespace for default values passed to the solver.
 *
 * In the case of the absence of solver arguments or invalid values
 * (for example, a negative value for the maximum number of iterations),
 * the corresponding default arguments are passed to the solver
 */
namespace DefaultSolverArgs
{
    const double TOLERANCE = 1e-6;
    const int MAX_ITER = 10000;
    const float SHIFT = 0.0;
}

/**
 * \brief Namespace for default values passed to the output generator.
 *
 * In the case of the absence of output arguments or invalid values
 * (for example, a filename with an extension different than txt),
 * the corresponding default arguments are passed to the output generator.
 */
namespace DefaultOutputArgs
{
    const std::string FILENAME = "output.txt";
}
#endif
