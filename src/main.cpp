#include <iostream>
#include <Eigen/Dense>

#include "constants.hpp"
#include "Config.hpp"
#include "MatrixGeneratorFactory.hpp"
#include "MatrixGenerator.hpp"
#include "MatrixGeneratorFromFile.hpp"
#include "MatrixGeneratorFromFunction.hpp"
#include "SolverFactory.hpp"
#include "PowerMethodSolver.hpp"
#include "InversePowerMethodSolver.hpp"
#include "QrMethodSolver.hpp"
#include "OutputGenerator.hpp"

// Instantiate the Matrix based on user args
template <typename T>
MatrixPointer<T> CreateMatrix(const std::string &inputName, const std::vector<std::string> &inputArgs)
{
    auto matrixGeneratorFactory = MatrixGeneratorFactory<T>(inputName, inputArgs);
    std::unique_ptr<MatrixGenerator<T>> generator = matrixGeneratorFactory.ChooseGenerator();
    MatrixPointer<T> matrixPointer = generator->GenerateMatrix();
    return matrixPointer;
}

// Solve the eigenvalue problem
template <typename T>
Vector<T> SolveProblem(const std::string &methodName, const std::vector<std::string> &methodArgs, MatrixPointer<T> matrixPointer)
{
    // Instantiate right solver based on methodName and methodArgs
    auto solverFactory = SolverFactory<T>(methodName, methodArgs);
    std::unique_ptr<AbstractIterativeSolver<T>> solver = solverFactory.ChooseSolver();
    solver->SetMatrix(matrixPointer);
    std::cout << "matrix: \n"
              << *matrixPointer << std::endl;

    // Solve eigenvalue problem
    Vector<T> eigenvalues = solver->FindEigenvalues();
    return eigenvalues;
}

template <typename T>
void OutputResults(const std::string &outputType, const std::vector<std::string> &outputArgs, Vector<T> eigenvalues)
{
    // Output eigenvalues
    OutputGenerator<T> outputGenerator(outputType, outputArgs, eigenvalues);
    outputGenerator.GenerateOutput();
}

// Output user args
void PrintParameters(Config &config)
{
    // Output parsed data
    std::cout << "==== USER PARAMETERS ====" << std::endl;

    std::cout << "Input Details:" << std::endl;
    std::cout << "  - Type: " << config.input.type << std::endl;
    std::cout << "  - Args:" << std::endl;
    for (const auto &inputArg : config.input.inputArgs)
    {
        std::cout << "      * " << inputArg << std::endl;
    }
    std::cout << "  - Data Type: " << config.type << std::endl;

    std::cout << "Method Details:" << std::endl;
    std::cout << "  - Method Name: " << config.method.name << std::endl;
    std::cout << "  - Method Args:" << std::endl;
    for (const auto &methodArg : config.method.methodArgs)
    {
        std::cout << "      * " << methodArg << std::endl;
    }

    std::cout << "Output Details:" << std::endl;
    std::cout << "  - Type: " << config.output.type << std::endl;
    std::cout << "  - Args:" << std::endl;
    for (const auto &outputArg : config.output.outputArgs)
    {
        std::cout << "      * " << outputArg << std::endl;
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
                "Usage: main <input_file.yaml>");
        else if (argc == 1)
            throw std::invalid_argument(
                "A YAML config file needs to be provided as argument.\n"
                "Usage: main <input_file.yaml>");
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
    PrintParameters(config);

    // Solve eigenvalue problem
    std::string type = config.type;
    MatrixVariant variantType;

    try
    {
        // Choose type first
        if (type == "float" || type == "int")
        {
            if (type == "int")
                std::cerr << "[WARNING] Implicit type conversion: 'int' to 'float': this may lead to loss of precision.\n"
                          << "          Consider using a float explicitly if this is intentional."
                          << std::endl;
            variantType = float{};
        }
        else if (type == "double")
        {
            variantType = double{};
        }
        else
        {
            throw std::runtime_error(type + " is a supported type but is not linked to a valid implementation.\n"
                                            "Consider updating the main() function to consider this type");
        }

        std::visit(
            [&](auto &&chosenType)
            {
                using ChosenType = std::decay_t<decltype(chosenType)>;
                MatrixPointer<ChosenType> matrixPointer = CreateMatrix<ChosenType>(config.input.type, config.input.inputArgs);
                Vector<ChosenType> eigenvalues = SolveProblem<ChosenType>(config.method.name, config.method.methodArgs, matrixPointer);
                OutputResults<ChosenType>(config.output.type, config.output.outputArgs, eigenvalues);
            },
            variantType);
    }
    // TODO: catch different exception types in different ways
    catch (const std::exception &e) // Catch exceptions
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
