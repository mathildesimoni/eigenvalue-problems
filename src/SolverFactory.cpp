#include "SolverFactory.hpp"
#include "PowerMethodSolver.hpp"
#include "InversePowerMethodSolver.hpp"
#include "QrMethodSolver.hpp"

template <typename T>
std::unique_ptr<AbstractIterativeSolver<T>> SolverFactory<T>::ChooseSolver()
{
    // Check validity of user input methodArgs
    if (methodArgs.size() > 3)
        throw std::invalid_argument("Expected maximum 3 arguments (tolerance, maximum iterations and shift), but got " + std::to_string(methodArgs.size()));
    // Declare and initialize methodArgs with default values
    double tolerance = 1e-6;
    int maxIter = 10000;
    float shift = 0.0;

    // Check tolerance input, set tolerance = 1e-6 if no arguments
    if (methodArgs.size() > 0)
    {
        try
        {
            tolerance = std::stod(methodArgs[0]);
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "Error processing the argument 'tolerance': " << e.what() << std::endl;
        }
    }

    // Check maxIter input, set maxIter = 10000 if no arguments
    if (methodArgs.size() > 1)
    {
        // Check max iterations input
        try
        {
            maxIter = std::stoi(methodArgs[1]);
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "Error processing the argument 'maxIter': " << e.what() << std::endl;
        }
    }
    // Check shift input, set shift = 0.0 if no arguments
    if (methodArgs.size() > 2)
    {
        try
        {
            shift = std::stof(methodArgs[2]);
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "Error processing the argument 'shift': " << e.what() << std::endl;
        }
    }

    std::unique_ptr<AbstractIterativeSolver<T>> solver;
    // Instantiate correct solver
    if (methodName == "power_method")
    {
        solver = std::make_unique<PowerMethodSolver<T>>(tolerance, maxIter, shift);
    }
    else if (methodName == "inverse_power_method")
    {
        solver = std::make_unique<InversePowerMethodSolver<T>>(tolerance, maxIter, shift);
    }
    else if (methodName == "QR_method")
    {
        solver = std::make_unique<QrMethodSolver<T>>(tolerance, maxIter);
    }
    else
    {
        throw std::invalid_argument("Unsupported method: " + methodName);
    }
    return solver;
}

// Explicit instantiation
template class SolverFactory<double>;
template class SolverFactory<float>;