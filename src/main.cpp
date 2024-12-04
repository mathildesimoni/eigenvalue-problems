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

// Instantiate the Matrix based on user args
template <typename T>
MatrixPointer<T> create_matrix(const std::string &input_name, const std::vector<std::string> &input_args)
{
    if (input_name == "function")
    {
        MatrixGeneratorFromFunction<T> generator(input_args);
        MatrixPointer<T> matrix_pointer = generator.generate_matrix();
        return matrix_pointer;
    }
    else // input_name == "file"
    {
        MatrixGeneratorFromFile<T> generator(input_args);
        MatrixPointer<T> matrix_pointer = generator.generate_matrix();
        return matrix_pointer;
    }
}

// Instantiate the solver based on user args
template <typename T>
std::unique_ptr<AbstractIterativeSolver<T>> create_solver(const std::string &method_name, const std::vector<std::string> &method_args)
{
    if (method_name == "power_method")
    {
        auto solver = std::make_unique<PowerMethodSolver<T>>();
        solver->SetMaxIter(std::stoi(method_args[0]));
        solver->SetTolerance(std::stof(method_args[1]));
        solver->SetShift(std::stof(method_args[2]));
        return solver;
    }
    else if (method_name == "inverse_power_method")
    {
        auto solver = std::make_unique<InversePowerMethodSolver<T>>();
        solver->SetMaxIter(std::stoi(method_args[0]));
        solver->SetTolerance(std::stof(method_args[1]));
        solver->SetShift(std::stof(method_args[2]));
        return solver;
    }
    else // method_name = "QR_method"
    {
        auto solver = std::make_unique<QrMethodSolver<T>>();
        solver->SetMaxIter(std::stoi(method_args[0]));
        solver->SetTolerance(std::stof(method_args[1]));
        return solver;
    }
}

// Solve the eigenvalue problem
template <typename T>
void solve(const Config &config)
{
    // Matrix generation
    auto matrix_pointer = create_matrix<T>(config.input.type, config.input.input_args);
    std::cout << *matrix_pointer << std::endl;
    std::cout << "Matrix pointer used to instantiate child class: " << matrix_pointer << std::endl;
    std::cout << "Solving with: " << config.method.name << std::endl;
    // TODO: remove above comments

    // Generate solver
    auto solver = create_solver<T>(config.method.name, config.method.method_args);
    solver->SetMatrix(*matrix_pointer);

    // Compute eigenvalues
    Vector<T> eigenvalues = solver->FindEigenvalues();

    // Output eigenvalues
    OutputGenerator<T> output_generator(config.output.type, config.output.output_arg, eigenvalues);
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
    std::cout << "  - Arg: " << config.output.output_arg << std::endl;

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
        std::cerr << "Error: " << e.what() << std::endl;
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

    if (type == "float" || type == "int")
    {
        if (type == "int")
            std::cerr << "[WARNING] Implicit type conversion: 'int' to 'float': this may lead to loss of precision.\n"
                      << "          Consider using a float explicitly if this is intentional."
                      << std::endl;
        variant_type = float{};
    }
    else // type = "double": user data type has been checked already to make sure it is among supported data types
    {
        variant_type = double{};
    }

    try
    {
        std::visit(
            [&](auto &&chosen_type)
            {
                using ChosenType = std::decay_t<decltype(chosen_type)>;
                solve<ChosenType>(config);
            },
            variant_type);
    }
    catch (const std::exception &e) // Catch exceptions
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
