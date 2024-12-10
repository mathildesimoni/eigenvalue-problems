#include <iostream>
#include <Eigen/Dense>
#include "Config.hpp"
#include "MatrixGenerator.hpp"
#include "MatrixGeneratorFromFile.hpp"
#include "MatrixGeneratorFromFunction.hpp"
#include "constants.hpp"
#include "PowerMethodSolver.hpp"
#include "InversePowerMethodSolver.hpp"
#include "QrMethodSolver.hpp"
#include "OutputGenerator.hpp"
#include "MatrixGeneratorFactory.hpp"

// Instantiate the Matrix based on user args
template <typename T>
MatrixPointer<T> create_matrix(const std::string &input_name, const std::vector<std::string> &input_args)
{
    auto matrix_generator_factory = MatrixGeneratorFactory<T>(input_name, input_args);
    std::unique_ptr<MatrixGenerator<T>> generator = matrix_generator_factory.choose_generator();
    MatrixPointer<T> matrix_pointer = generator->generate_matrix();
    return matrix_pointer;
}

// Solve the eigenvalue problem
template <typename T>
Vector<T> solve_problem(const std::string &method_name, const std::vector<std::string> &method_args, MatrixPointer<T> matrix_pointer)
{
    std::unique_ptr<AbstractIterativeSolver<T>> solver;

    if (method_name == "power_method")
    {
        auto power_solver = std::make_unique<PowerMethodSolver<T>>(std::stof(method_args[0]), std::stoi(method_args[1]), std::stof(method_args[2]));
        // if (method_args.size() > 2)
            // power_solver->SetShift(std::stof(method_args[2]));
        // else
            // power_solver->SetShift(0.0);
        // power_solver->SetShift(std::stof(method_args[2]));
        solver = std::move(power_solver);
    }
    else if (method_name == "inverse_power_method")
    {
        auto inverse_power_solver = std::make_unique<InversePowerMethodSolver<T>>(std::stof(method_args[0]), std::stoi(method_args[1]), std::stof(method_args[2]));
        // if (method_args.size() > 2)
            // inverse_power_solver->SetShift(std::stof(method_args[2]));
        // else
            // inverse_power_solver->SetShift(0.0);
        // inverse_power_solver->SetShift(std::stof(method_args[2]));
        solver = std::move(inverse_power_solver);
    }
    else if (method_name == "QR_method")
    {
        solver = std::make_unique<QrMethodSolver<T>>(std::stof(method_args[0]), std::stoi(method_args[1]));
    }
    else
    {
        throw std::runtime_error(method_name + " is a supported method but is not linked to a valid implementation.\n"
                                               "Consider updating the solve_problem() function to consider this method");
    }

    // TODO: try and catch if args are not numbers?
    // solver->SetMaxIter(std::stoi(method_args[0]));
    // solver->SetTolerance(std::stof(method_args[1]));
    solver->SetMatrix(matrix_pointer);

    // Compute eigenvalues
    Vector<T> eigenvalues = solver->FindEigenvalues();

    return eigenvalues;
}

template <typename T>
void output_results(const std::string &output_type, const std::vector<std::string> &output_args, Vector<T> eigenvalues)
{
    // Output eigenvalues
    OutputGenerator<T> output_generator(output_type, output_args, eigenvalues);
    output_generator.generate_output();
}

// Output user args
void print_parameters(Config &config)
{
    // Output parsed data
    std::cout << "==== USER PARAMETERS ====" << std::endl;

    std::cout << "Input Details:" << std::endl;
    std::cout << "  - Type: " << config.input.type << std::endl;
    std::cout << "  - Args:" << std::endl;
    for (const auto &input_arg : config.input.input_args)
    {
        std::cout << "    * " << input_arg << std::endl;
    }
    std::cout << "  - Data Type: " << config.type << std::endl;

    std::cout << "Method Details:" << std::endl;
    std::cout << "  - Method Name: " << config.method.name << std::endl;
    std::cout << "  - Method Args:" << std::endl;
    for (const auto &method_arg : config.method.method_args)
    {
        std::cout << "      * " << method_arg << std::endl;
    }

    std::cout << "Output Details:" << std::endl;
    std::cout << "  - Type: " << config.output.type << std::endl;
    std::cout << "  - Args:" << std::endl;
    for (const auto &output_arg : config.output.output_args)
    {
        std::cout << "    * " << output_arg << std::endl;
    }
    std::cout << "=========================" << std::endl;
}

int main(int argc, char *argv[])
{
    // Parse input YAML config file and catch errors
    Config config;
    try
    {
        if (argc > 2)
            throw std::invalid_argument(
                "Only one argument is allowed: a YAML config file.\n"
                "Usage: main <inputfile.yaml>");
        else if (argc == 1)
            throw std::invalid_argument(
                "A YAML config file needs to be provided as argument.\n"
                "Usage: main <inputfile.yaml>");
        config = parseYAML(std::string(Paths::PATH_INPUT_FILE).append(argv[1])); // Parse the YAML file
    }
    catch (const std::invalid_argument &e) // Catch our own thrown exceptions
    {
        std::cerr << "Error (user input): " << e.what() << std::endl;
        return -1;
    }
    catch (const std::exception &e) // Catch exceptions from yaml-cpp library
    {
        std::cerr << "Error during config file parsing: " << e.what() << std::endl;
        return -1;
    }

    // Print parameters
    print_parameters(config);

    // Solve eigenvalue problem
    std::string type = config.type;
    MatrixVariant variant_type;

    try
    {
        // Choose type first
        if (type == "float" || type == "int")
        {
            if (type == "int")
                std::cerr << "[WARNING] Implicit type conversion: 'int' to 'float': this may lead to loss of precision.\n"
                          << "          Consider using a float explicitly if this is intentional."
                          << std::endl;
            variant_type = float{};
        }
        else if (type == "double")
        {
            variant_type = double{};
        }
        else
        {
            throw std::runtime_error(type + " is a supported type but is not linked to a valid implementation.\n"
                                            "Consider updating the main() function to consider this type");
        }

        std::visit(
            [&](auto &&chosen_type)
            {
                using ChosenType = std::decay_t<decltype(chosen_type)>;
                MatrixPointer<ChosenType> matrix_pointer = create_matrix<ChosenType>(config.input.type, config.input.input_args);
                Vector<ChosenType> eigenvalues = solve_problem<ChosenType>(config.method.name, config.method.method_args, matrix_pointer);
                output_results<ChosenType>(config.output.type, config.output.output_args, eigenvalues);
            },
            variant_type);
    }
    // TODO: catch different exception types in different ways
    catch (const std::exception &e) // Catch exceptions
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
