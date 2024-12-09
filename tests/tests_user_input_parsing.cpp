#include <cmath>
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include "Config.hpp"

TEST(parse_user_args, invalid_yaml_file)
{
    // Create a temporary YAML file with invalid input type
    const std::string invalid_yaml_file = "invalid_input.yaml";
    std::ofstream yaml_file(invalid_yaml_file);
    yaml_file << "  type: file\n" // forgot 1 line "input"
                 "  input_args:\n"
                 "    - A.csv\n"
                 "type: int\n"
                 "method:\n"
                 "  name: power_method\n"
                 "  method_args:\n"
                 "    - 50000\n"
                 "    - 10e-6\n"
                 "    - 0\n"
                 "output:\n"
                 "  type: save\n"
                 "  output_arg: output.txt\n";
    yaml_file.close();

    // Make sure that parseYAML throws an exception
    EXPECT_THROW(parseYAML(invalid_yaml_file), std::exception);

    // Clean up the temporary file
    std::remove(invalid_yaml_file.c_str());
}

TEST(parse_user_args, invalid_input_type)
{
    // Create a temporary YAML file with invalid input type
    const std::string invalid_yaml_file = "invalid_input.yaml";
    std::ofstream yaml_file(invalid_yaml_file);
    yaml_file << "input:\n"
                 "  type: invalid_input_type\n" // Invalid type
                 "  input_args:\n"
                 "    - A.csv\n"
                 "type: int\n"
                 "method:\n"
                 "  name: power_method\n"
                 "  method_args:\n"
                 "    - 50000\n"
                 "    - 10e-6\n"
                 "    - 0\n"
                 "output:\n"
                 "  type: print\n"
                 "  output_arg: output.txt\n";
    yaml_file.close();

    // Make sure that parseYAML throws an exception
    EXPECT_THROW(parseYAML(invalid_yaml_file), std::invalid_argument);

    // Clean up the temporary file
    std::remove(invalid_yaml_file.c_str());
}

TEST(parse_user_args, invalid_data_type)
{
    // Create a temporary YAML file with invalid input type
    const std::string invalid_yaml_file = "invalid_input.yaml";
    std::ofstream yaml_file(invalid_yaml_file);
    yaml_file << "input:\n"
                 "  type: file\n"
                 "  input_args:\n"
                 "    - A.csv\n"
                 "type: invalid_data_type\n" // invalid data type
                 "method:\n"
                 "  name: power_method\n"
                 "  method_args:\n"
                 "    - 50000\n"
                 "    - 10e-6\n"
                 "    - 0\n"
                 "output:\n"
                 "  type: print\n"
                 "  output_arg: output.txt\n";
    yaml_file.close();

    // Make sure that parseYAML throws an exception
    EXPECT_THROW(parseYAML(invalid_yaml_file), std::invalid_argument);

    // Clean up the temporary file
    std::remove(invalid_yaml_file.c_str());
}

TEST(parse_user_args, invalid_method_name)
{
    // Create a temporary YAML file with invalid input type
    const std::string invalid_yaml_file = "invalid_input.yaml";
    std::ofstream yaml_file(invalid_yaml_file);
    yaml_file << "input:\n"
                 "  type: file\n"
                 "  input_args:\n"
                 "    - A.csv\n"
                 "type: int\n"
                 "method:\n"
                 "  name: invalid_method\n" // invalid method
                 "  method_args:\n"
                 "    - 50000\n"
                 "    - 10e-6\n"
                 "    - 0\n"
                 "output:\n"
                 "  type: print\n"
                 "  output_arg: output.txt\n";
    yaml_file.close();

    // Make sure that parseYAML throws an exception
    EXPECT_THROW(parseYAML(invalid_yaml_file), std::invalid_argument);

    // Clean up the temporary file
    std::remove(invalid_yaml_file.c_str());
}

TEST(parse_user_args, invalid_output_type)
{
    // Create a temporary YAML file with invalid input type
    const std::string invalid_yaml_file = "invalid_input.yaml";
    std::ofstream yaml_file(invalid_yaml_file);
    yaml_file << "input:\n"
                 "  type: file\n"
                 "  input_args:\n"
                 "    - A.csv\n"
                 "type: int\n"
                 "method:\n"
                 "  name: power_method\n"
                 "  method_args:\n"
                 "    - 50000\n"
                 "    - 10e-6\n"
                 "    - 0\n"
                 "output:\n"
                 "  type: invalid_output_type\n" // invalid output type
                 "  output_arg: output.txt\n";
    yaml_file.close();

    // Make sure that parseYAML throws an exception
    EXPECT_THROW(parseYAML(invalid_yaml_file), std::invalid_argument);

    // Clean up the temporary file
    std::remove(invalid_yaml_file.c_str());
}