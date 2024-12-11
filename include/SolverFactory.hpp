#ifndef __SOLVER_FACTORY_HPP__
#define __SOLVER_FACTORY_HPP__

#include <iostream>
#include <string>
#include "constants.hpp"
#include "AbstractIterativeSolver.hpp"

/**
 * \brief Factory class to generate different types of solvers.
 *
 * This factory class is responsible for creating instances of solvers based on user input.
 * It determines the appropriate solver and constructs it accordingly.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class SolverFactory
{
public:
    SolverFactory(const std::string &methodName, const std::vector<std::string> &methodArgs) : methodName(methodName), methodArgs(methodArgs) {};
    ~SolverFactory() {};
    /**
     * \brief Select the right solver for the eigenvalue problem based on the method
     * name specified by the user.
     *
     * This method evaluates the method name (`methodName`) and create the solver
     * with the right arguments (`methodArgs`). The method also checks that the
     * method arguments are valid, and converts them to the right type.
     *
     * \return A unique pointer to a solver object.
     */
    std::unique_ptr<AbstractIterativeSolver<T>> ChooseSolver();

private:
    const std::string &methodName;              /**< The name of the solver method. */
    const std::vector<std::string> &methodArgs; /**< Arguments relative to the solver. */
};

#endif