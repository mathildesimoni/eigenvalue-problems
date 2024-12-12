#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>

#include <yaml-cpp/yaml.h>

/**
 * \brief Sructure to hold the configuration settings parsed from a YAML file.
 *
 * This structure is used to store the input, method, and output configurations
 * for the application.
 */
struct Config
{
    /// Structure to hold the input parameters
    struct Input
    {
        std::string type;
        std::vector<std::string> inputArgs;
    } input;

    std::string type;

    /// Structure to hold the method parameters
    struct Method
    {
        std::string name;
        std::vector<std::string> methodArgs;
    } method;

    /// Structure to hold the output parameters
    struct Output
    {
        std::string type;
        std::vector<std::string> outputArgs;
    } output;
};

/**
 * \brief Parses a YAML configuration file and returns a Config structure.
 *
 * This function reads a YAML configuration file, extracts the relevant
 * information. It also checks that the arguments are among the accepted
 * arguments stored in constants.hpp
 *
 * \param fileName The name of the YAML configuration file to be parsed.
 * \return A Config structure containing the parsed configuration data.
 */
Config parseYAML(const std::string &fileName);

#endif