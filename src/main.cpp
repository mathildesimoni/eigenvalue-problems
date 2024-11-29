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

// Matrix Generator without having to specify the type
template <typename T>
MatrixPointer<T> create_matrix(const std::string &input_name, const std::vector<std::string> &input_args)
{
    if (input_name == "function")
    {
        MatrixGeneratorFromFunction<T> generator(input_args);
        MatrixPointer<T> matrix_pointer = generator.generate_matrix();
        return matrix_pointer;
    }
    else if (input_name == "file")
    {
        MatrixGeneratorFromFile<T> generator(input_args);
        MatrixPointer<T> matrix_pointer = generator.generate_matrix();
        return matrix_pointer;
    }
    else
    {
        throw std::invalid_argument("Unknown input type: " + input_name);
    }
}

// using Param = std::vectoir;
// Factory method for the solver
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
    else if (method_name == "QR_method")
    {
        auto solver = std::make_unique<QrMethodSolver<T>>();
        solver->SetMaxIter(std::stoi(method_args[0]));
        solver->SetTolerance(std::stof(method_args[1]));
        return solver;
    }
    else
    {
        throw std::invalid_argument("Unknown solver type: " + method_name);
    }
}

// Templated function to process matrices and solvers
template <typename T>
void solve(const Config &config)
{
    // Matrix generation
    auto matrix_pointer = create_matrix<T>(config.input.type, config.input.input_args);
    std::cout << *matrix_pointer << std::endl;

    std::cout << "Solving with: " << config.method.name << std::endl;

    try
    {
        // Generate solver
        auto solver = create_solver<T>(config.method.name, config.method.method_args);
        solver->SetMatrix(matrix_pointer);

        // Compute eigenvalues
        Eigen::Matrix<T, Eigen::Dynamic, 1> eigenvalue = solver->FindEigenvalues();
        std::cout << "Computed Eigenvalue: " << eigenvalue << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    // Parse input YAML config file
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
        // TODO: say what to do, suggestion
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

    std::string type = config.type;

    // Solve eigenvalue problem
    MatrixVariant variant_type;
    if (type == "float" || type == "int")
    {
        // why does this work???
        if (type == "int")
            std::cout << "WARNING: Casting int to float!" << std::endl; // TODO: better error message
        variant_type = float{};
    }
    else if (type == "double")
    {
        variant_type = double{};
    }
    else
    {
        throw std::invalid_argument("Unsupported type:" + type);
    }
    std::visit(
        [&](auto &&chosen_type)
        {
            using ChosenType = std::decay_t<decltype(chosen_type)>;
            solve<ChosenType>(config);
        },
        variant_type);

    Eigen::Matrix<float, Eigen::Dynamic, 1> tryout_data(5);
    tryout_data << 1.0f, 2.0f, 3.0f, 4.0f, 5.0f;
    OutputGenerator<float> generator(config.output.type, config.output.output_arg, tryout_data);
    generator.generate_output();

    return 0;
}
