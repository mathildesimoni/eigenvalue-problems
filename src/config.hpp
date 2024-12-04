#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>
#include <yaml-cpp/yaml.h>

struct Config
{
    struct Input
    {
        std::string type;
        std::vector<std::string> input_args;
    } input;

    std::string type;

    struct Method
    {
        std::string name;
        std::vector<std::string> method_args;
    } method;

    struct Output
    {
        std::string type;
        std::vector<std::string> output_args;
    } output;
};

// Function to parse the YAML configuration file
Config parseYAML(const std::string &filename);

#endif