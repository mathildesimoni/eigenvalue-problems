#include "SolverFactory.hpp"
#include "AbstractIterativeSolver.hpp"
#include "PowerMethodSolver.hpp"
#include "InversePowerMethodSolver.hpp"
#include "QrMethodSolver.hpp"
#include <stdexcept>

template <typename T>
std::unique_ptr<AbstractIterativeSolver<T>> SolverFactory<T>::choose_solver()
{
    // Check validity of user input method_args
    if (method_args.size() > 3)
        throw std::invalid_argument("Expected maximum 3 arguments (tolerance, maximum iterations and shift), but got " + std::to_string(method_args.size()));
    // Declare and initialize method_args with default values
    double tolerance = 1e-6;
    int max_iter = 10000;
    float shift = 0.0;

    // Check tolerance input, set tolerance = 1e-6 if no arguments
    if (method_args.size() > 0)
    {
        try {
            tolerance = std::stod(method_args[0]);
        } 
        catch (std::invalid_argument &e) 
        {
            std::cerr << "Error processing the argument 'tolerance': " << e.what() << std::endl;
        }
    }

    // Check max_iter input, set max_iter = 10000 if no arguments
    if (method_args.size() > 1)
    {
        // Check max iterations input
        try {
            max_iter = std::stoi(method_args[1]);
        } 
        catch (std::invalid_argument &e) 
        {
            std::cerr << "Error processing the argument 'max_iter': " << e.what() << std::endl;
        }
    }
    // Check shift input, set shift = 0.0 if no arguments
    if (method_args.size() > 2)
    {
        try {
            shift = std::stof(method_args[2]);
        } 
        catch (std::invalid_argument &e) 
        {
            std::cerr << "Error processing the argument 'shift': " << e.what() << std::endl;
        }
    }

    std::unique_ptr<AbstractIterativeSolver<T>> solver;
    // instantiate correct solver
    if (method_name == "power_method")
    {
        solver = std::make_unique<PowerMethodSolver<T>>(tolerance, max_iter, shift);
    }
    else if (method_name == "inverse_method_method")
    {
        solver = std::make_unique<InversePowerMethodSolver<T>>(tolerance, max_iter, shift);
    }
    else if (method_name == "QR_method")
    {
        solver = std::make_unique<QrMethodSolver<T>>(tolerance, max_iter);
    }
    else
    {
        throw std::invalid_argument("Unsupported method: " + method_name);
    }
    return solver;
}

// Explicit instantiation
template class SolverFactory<double>;
template class SolverFactory<float>;