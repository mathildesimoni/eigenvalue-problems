#include <iostream>
#include <Eigen/Dense>
#include "test_class.hpp"
#include "config.hpp"

int main(int argc, char *argv[])
{

    if (argc > 2)
        throw std::invalid_argument("Only 1 argument can be provied: a YAML config file.");
    else if (argc == 1)
        throw std::invalid_argument("A YAML config file needs to be provided as argument.");

    Config config;
    try
    {
        config = parseYAML(std::string("../input/").append(argv[1])); // Parse the YAML file
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Output parsed data
    std::cout << "Input Type: " << config.input.type << std::endl;
    std::cout << "Input Arg: " << config.input.input_arg << std::endl;
    std::cout << "Type: " << config.type << std::endl;
    std::cout << "Method Name: " << config.method.name << std::endl;
    std::cout << "Max Iterations: " << config.method.method_args.max_iter << std::endl;
    std::cout << "Epsilon: " << config.method.method_args.epsilon << std::endl;
    std::cout << "Output Type: " << config.output.type << std::endl;
    std::cout << "Output Arg: " << config.output.output_arg << std::endl;

    // // Tryout for Eigen library
    // Eigen::MatrixXd m(3, 3);
    // std::cout << "nb_rows: " << m.rows() << std::endl;
    // std::cout << "nb_cols: " << m.cols() << std::endl;
    // std::cout << "size: " << m.size() << std::endl;
    // std::cout << "m = " << m << std::endl;
    // std::cout << "m.T = " << m.transpose() << std::endl;

    // // Test include test_class
    // int test_return_value = foo();
    // std::cout << "Return value test: " << test_return_value << std::endl;

    return 0;
}