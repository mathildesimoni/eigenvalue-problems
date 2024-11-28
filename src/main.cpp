#include <iostream>
#include <Eigen/Dense>
#include "test_class.hpp"
#include "Config.hpp"
#include "MatrixGenerator.hpp"
#include "MatrixGeneratorFromFile.hpp"
#include "MatrixGeneratorFromFunction.hpp"
#include "constants.hpp"
#include "PowerMethodSolver.hpp"
#include "InversePowerMethodSolver.hpp"
#include "OutputGenerator.hpp"

int main(int argc, char *argv[])
{

    if (argc > 2)
        throw std::invalid_argument("Only 1 argument can be provied: a YAML config file.");
    else if (argc == 1)
        throw std::invalid_argument("A YAML config file needs to be provided as argument.");

    Config config;
    try
    {
        config = parseYAML(std::string(Paths::PATH_INPUT_FILE).append(argv[1])); // Parse the YAML file
    }
    catch (const std::invalid_argument &e) // Catch our own thrown exceptions
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    catch (const std::exception &e) // Catch exceptions from yaml-cpp library
    {
        std::cerr << "Error during config file parsing: " << e.what() << std::endl;
        return -1;
    }

    // Output parsed data
    std::cout << "Input Type: " << config.input.type << std::endl;
    std::cout << "Input Args: " << std::endl;
    for (const auto &input_arg : config.input.input_args)
    {
        std::cout << "- " << input_arg << std::endl;
    }
    std::cout << "Type: " << config.type << std::endl;
    std::cout << "Method Name: " << config.method.name << std::endl;
    std::cout << "Method Args: " << std::endl;
    for (const auto &method_arg : config.method.method_args)
    {
        std::cout << "- " << method_arg << std::endl;
    }
    std::cout << "Output Type: " << config.output.type << std::endl;
    std::cout << "Output Arg: " << config.output.output_arg << std::endl;

    // tryout
    // TODO: factory method or other function to instantiate the matrix
    std::string type = config.type;

    if (config.input.type == "file")
    {
        if (type == "float" || type == "int")
        {
            if (type == "int")
                std::cout << "WARNING: Casting int to float!" << std::endl; // TODO: better error message
            MatrixGeneratorFromFile<float> generator = MatrixGeneratorFromFile<float>(config.input.input_args);
            std::unique_ptr<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>> matrix_pointer = generator.generate_matrix();
            std::cout << *matrix_pointer << std::endl;
        }
        else if (type == "double")
        {
            MatrixGeneratorFromFile<double> generator = MatrixGeneratorFromFile<double>(config.input.input_args);
            std::unique_ptr<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> matrix_pointer = generator.generate_matrix();
            std::cout << *matrix_pointer << std::endl;
        }
        else
        {
            throw std::invalid_argument("Unsupported type: " + type);
        }
    }
    else if (config.input.type == "function")
    {
        if (type == "float" || type == "int")
        {
            if (type == "int")
                std::cout << "WARNING: Casting int to float!" << std::endl; // TODO: better error message
            MatrixGeneratorFromFunction<float> generator = MatrixGeneratorFromFunction<float>(config.input.input_args);
            std::unique_ptr<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>> matrix_pointer = generator.generate_matrix();
            std::cout << *matrix_pointer << std::endl;

            // solver part
            if (config.method.name == "power_method") {
                std::cout << "Solving with the power method" << std::endl;
                PowerMethodSolver<float> solver;

                // set arguments and convert to the right type
                solver.SetMaxIter(std::stoi(config.method.method_args[0]));
                solver.SetTolerance(std::stof(config.method.method_args[1]));
                solver.SetShift(std::stof(config.method.method_args[2]));
                solver.SetMatrix(*matrix_pointer);

                Eigen::Matrix<float, Eigen::Dynamic, 1>  eigenvalue = solver.FindEigenvalues();
                std::cout << "Computed Eigenvalue: " << eigenvalue << std::endl;

            } else if (config.method.name == "inverse_power_method") {
                
                std::cout << "Solving with the inverse power method" << std::endl;
                InversePowerMethodSolver<float> solver;

                // set arguments and convert to the right type
                solver.SetMaxIter(std::stoi(config.method.method_args[0]));
                solver.SetTolerance(std::stof(config.method.method_args[1]));
                solver.SetShift(std::stof(config.method.method_args[2]));
                solver.SetMatrix(*matrix_pointer);

                Eigen::Matrix<float, Eigen::Dynamic, 1>  eigenvalue = solver.FindEigenvalues();
                std::cout << "Computed Eigenvalue: " << eigenvalue << std::endl;

            }
        }
        else if (type == "double")
        {
            MatrixGeneratorFromFunction<double> generator = MatrixGeneratorFromFunction<double>(config.input.input_args);
            std::unique_ptr<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> matrix_pointer = generator.generate_matrix();
            std::cout << *matrix_pointer << std::endl;

            // solver part
            if (config.method.name == "power_method") {
                std::cout << "Solving with the power method" << std::endl;
                PowerMethodSolver<double> solver;

                // set arguments and convert to the right type
                solver.SetMaxIter(std::stoi(config.method.method_args[0]));
                solver.SetTolerance(std::stof(config.method.method_args[1]));
                solver.SetShift(std::stof(config.method.method_args[2]));
                solver.SetMatrix(*matrix_pointer);

                Eigen::Matrix<double, Eigen::Dynamic, 1>  eigenvalue = solver.FindEigenvalues();
                std::cout << "Computed Eigenvalue: " << eigenvalue << std::endl;

            } else if (config.method.name == "inverse_power_method") {
                
                std::cout << "Solving with the inverse power method" << std::endl;
                InversePowerMethodSolver<double> solver;

                // set arguments and convert to the right type
                solver.SetMaxIter(std::stoi(config.method.method_args[0]));
                solver.SetTolerance(std::stof(config.method.method_args[1]));
                solver.SetShift(std::stof(config.method.method_args[2]));
                solver.SetMatrix(*matrix_pointer);

                Eigen::Matrix<double, Eigen::Dynamic, 1>  eigenvalue = solver.FindEigenvalues();
                std::cout << "Computed Eigenvalue: " << eigenvalue << std::endl;

            }
        }
        else
        {
            throw std::invalid_argument("Unsupported type: " + type);
        }
    }

    // tryout for output handling
    std::vector<float> tryout_data = {1.0, 2.0, 3.0, 4.0, 5.0};
    OutputGenerator<float> generator(config.output.type, config.output.output_arg, tryout_data);
    generator.generate_output();

    // // Test include test_class
    // int test_return_value = foo();
    // std::cout << "Return value test: " << test_return_value << std::endl;

    return 0;
}
