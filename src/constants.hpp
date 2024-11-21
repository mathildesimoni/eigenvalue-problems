#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

#include <set>
#include <string>

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
