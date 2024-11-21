#include <iostream>
#include <fstream>
#include <stdexcept>

#include "config.hpp"

Config parseYAML(const std::string &filename)
{
    YAML::Node config = YAML::LoadFile(filename);
    Config parsed_config;

    if (config["input"])
    {
        parsed_config.input.type = config["input"]["type"].as<std::string>();
        parsed_config.input.input_arg = config["input"]["input_arg"].as<std::string>();
    }

    if (config["type"])
    {
        parsed_config.type = config["type"].as<std::string>();
    }

    if (config["method"])
    {
        parsed_config.method.name = config["method"]["name"].as<std::string>();
        if (config["method"]["method_args"])
        {
            parsed_config.method.method_args.max_iter = config["method"]["method_args"]["max_iter"].as<int>();
            parsed_config.method.method_args.epsilon = config["method"]["method_args"]["epsilon"].as<double>();
        }
    }

    if (config["output"])
    {
        parsed_config.output.type = config["output"]["type"].as<std::string>();
        parsed_config.output.output_arg = config["output"]["output_arg"].as<std::string>();
    }

    return parsed_config;
}