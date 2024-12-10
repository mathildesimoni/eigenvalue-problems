#ifndef __SOLVER_FACTORY_HPP__
#define __SOLVER_FACTORY_HPP__

#include <iostream>
#include <string>
#include "constants.hpp"
#include "AbstractIterativeSolver.hpp"

template <typename T>
class SolverFactory
{
public:
    SolverFactory(const std::string &method_name, const std::vector<std::string> &method_args) : method_name(method_name), method_args(method_args) {};
    ~SolverFactory() {};
    /**
     * \brief Select the right solver for the eigenvalue problem based on the method
     * name specified by the user.
     *
     * This method evaluates the method name (`method_name`) and create the solver
     * with the right arguments (`method_args`). The method also checks that the
     * method arguments are valid, and converts them to the right type.
     *
     * \return A unique pointer to a solver object.
     */
    std::unique_ptr<AbstractIterativeSolver<T>> choose_solver();

private:
    const std::string &method_name;              /**< The name of the solver method. */
    const std::vector<std::string> &method_args; /**< Arguments relative to the solver. */
};

#endif