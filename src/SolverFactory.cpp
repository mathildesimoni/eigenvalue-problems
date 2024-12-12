#include "SolverFactory.hpp"
#include "PowerMethodSolver.hpp"
#include "InversePowerMethodSolver.hpp"
#include "QrMethodSolver.hpp"

template <typename T>
std::unique_ptr<AbstractIterativeSolver<T>> SolverFactory<T>::ChooseSolver()
{
    // Check validity of user input methodArgs
    if (methodArgs.size() > 3)
        throw std::invalid_argument("Expected maximum 3 arguments (tolerance, maximum iterations and shift), but got " + std::to_string(methodArgs.size()) + " (in SolverFactory)");
    // Declare and initialize methodArgs with default values
    double tolerance = DefaultSolverArgs::TOLERANCE;
    int maxIter = DefaultSolverArgs::MAX_ITER;
    float shift = DefaultSolverArgs::SHIFT;

    // Check tolerance input, set tolerance = 1e-6 if no argument or invalue argument
    if (methodArgs.size() > 0)
    {
        try
        {
            double toleranceTmp = std::stod(methodArgs[0]);
            if (toleranceTmp <= 0.0)
                throw std::invalid_argument("The tolerance must be a positive number, but got " + std::to_string(toleranceTmp));
            tolerance = toleranceTmp;
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "[WARNING] Error processing the argument 'tolerance' in SolverFactory: " << e.what() << std::endl
                      << "          Handling the issue by setting 'tolerance' to the default value (" << std::to_string(tolerance) << ")"
                      << std::endl;
        }
    }

    // Check maxIter input, set maxIter = 10000 if no arguments or invalid argument
    if (methodArgs.size() > 1)
    {
        // Check max iterations input
        try
        {
            int maxIterTmp = std::stoi(methodArgs[1]);
            if (maxIterTmp <= 0.0)
                throw std::invalid_argument("The maximum number of iterations must be a positive integer, but got " + std::to_string(maxIterTmp));
            maxIter = maxIterTmp;
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "[WARNING] Error processing the argument 'maxIter' in SolverFactory: " << e.what() << std::endl
                      << "          Handling the issue by setting 'maxIter' to the default value (" << std::to_string(maxIter) << ")"
                      << std::endl;
        }
    }
    // Check shift input, set shift = 0.0 if no arguments or invalid argument
    if (methodArgs.size() > 2)
    {
        try
        {
            shift = std::stof(methodArgs[2]);
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "[WARNING] Error processing the argument 'shift' in SolverFactory: " << e.what() << std::endl
                      << "          Handling the issue by setting 'shift' to the default value (" << std::to_string(shift) << ")"
                      << std::endl;
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
        throw std::runtime_error(methodName + " is a supported method but is not linked to a valid implementation.\n"
                                              "Consider updating the SolverFactory to consider this method");
    }
    return solver;
}

// Explicit instantiation
template class SolverFactory<double>;
template class SolverFactory<float>;