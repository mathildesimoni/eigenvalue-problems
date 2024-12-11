#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Config.hpp"
#include "constants.hpp"

Config parseYAML(const std::string &fileName)
{
    YAML::Node config = YAML::LoadFile(fileName);
    Config parsedConfig;

    parsedConfig.input.type = config["input"]["type"].as<std::string>();
    if (SupportedArguments::SUPPORTED_INPUT_TYPES.find(parsedConfig.input.type) == SupportedArguments::SUPPORTED_INPUT_TYPES.end())
    {
        throw std::invalid_argument("unsupported input type (" + parsedConfig.input.type + ")");
    }
    parsedConfig.input.inputArgs = config["input"]["input_args"].as<std::vector<std::string>>();

    parsedConfig.type = config["type"].as<std::string>();
    if (SupportedArguments::SUPPORTED_TYPES.find(parsedConfig.type) == SupportedArguments::SUPPORTED_TYPES.end())
    {
        throw std::invalid_argument("unsupported type (" + parsedConfig.type + ")");
    }

    parsedConfig.method.name = config["method"]["name"].as<std::string>();
    if (SupportedArguments::SUPPORTED_METHODS.find(parsedConfig.method.name) == SupportedArguments::SUPPORTED_METHODS.end())
    {
        throw std::invalid_argument("unsupported method (" + parsedConfig.method.name + ")");
    }
    parsedConfig.method.methodArgs = config["method"]["method_args"].as<std::vector<std::string>>();

    parsedConfig.output.type = config["output"]["type"].as<std::string>();
    if (SupportedArguments::SUPPORTED_OUTPUT_TYPES.find(parsedConfig.output.type) == SupportedArguments::SUPPORTED_OUTPUT_TYPES.end())
    {
        throw std::invalid_argument("unsupported output type (" + parsedConfig.output.type + ")");
    }
    parsedConfig.output.outputArgs = config["output"]["output_args"].as<std::vector<std::string>>();

    return parsedConfig;
}