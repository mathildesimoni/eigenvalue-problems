#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

#include <set>
#include <string>
#include <Eigen/Dense>

using MatrixVariant = std::variant<float, double>;

template <typename T>
using MatrixPointer = std::shared_ptr<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>; 

template <typename T>
using Matrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

template <typename T>
using Vector = Eigen::Matrix<T, Eigen::Dynamic, 1>;

// Define paths to inputs and outputs
namespace Paths
{
    const std::string PATH_INPUT_FILE = "../input/";
    const std::string PATH_MATRICES = "../input/matrices/";
    const std::string PATH_OUTPUT_FILE = "../output/";
}

// Define lists of supported inputs
namespace SupportedArguments
{
    // Supported types for matrices
    const std::set<std::string> SUPPORTED_TYPES = {
        "int",
        "float",
        "double"};

    // Supported methods
    const std::set<std::string> SUPPORTED_METHODS = {
        "power_method",
        "power_method_with_shift",
        "inverse_power_method",
        "inverse_power_method_with_shift",
        "QR_method"};

    // Supported input types
    const std::set<std::string> SUPPORTED_INPUT_TYPES = {
        "file",
        "function"};

    // Supported output actions
    const std::set<std::string> SUPPORTED_OUTPUT_TYPES = {
        "print",
        "save"};
}
#endif
