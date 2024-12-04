#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Config.hpp"
#include "constants.hpp"

Config parseYAML(const std::string &filename)
{
    YAML::Node config = YAML::LoadFile(filename);
    Config parsed_config;

    parsed_config.input.type = config["input"]["type"].as<std::string>();
    if (SupportedArguments::SUPPORTED_INPUT_TYPES.find(parsed_config.input.type) == SupportedArguments::SUPPORTED_INPUT_TYPES.end())
    {
        throw std::invalid_argument("unsupported input type (" + parsed_config.input.type + ")");
    }
    parsed_config.input.input_args = config["input"]["input_args"].as<std::vector<std::string>>();

    parsed_config.type = config["type"].as<std::string>();
    if (SupportedArguments::SUPPORTED_TYPES.find(parsed_config.type) == SupportedArguments::SUPPORTED_TYPES.end())
    {
        throw std::invalid_argument("unsupported type (" + parsed_config.type + ")");
    }

    parsed_config.method.name = config["method"]["name"].as<std::string>();
    if (SupportedArguments::SUPPORTED_METHODS.find(parsed_config.method.name) == SupportedArguments::SUPPORTED_METHODS.end())
    {
        throw std::invalid_argument("unsupported method (" + parsed_config.method.name + ")");
    }
    parsed_config.method.method_args = config["method"]["method_args"].as<std::vector<std::string>>();

    parsed_config.output.type = config["output"]["type"].as<std::string>();
    if (SupportedArguments::SUPPORTED_OUTPUT_TYPES.find(parsed_config.output.type) == SupportedArguments::SUPPORTED_OUTPUT_TYPES.end())
    {
        throw std::invalid_argument("unsupported output type (" + parsed_config.output.type + ")");
    }
    parsed_config.output.output_args = config["output"]["output_args"].as<std::vector<std::string>>();

    return parsed_config;
}