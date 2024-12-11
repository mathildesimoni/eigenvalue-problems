#ifndef __MATRIX_FACTORY_HPP__
#define __MATRIX_FACTORY_HPP__

#include <iostream>
#include <string>
#include "constants.hpp"
#include "MatrixGenerator.hpp"

/**
 * \brief Factory class to generate different types of matrix generators.
 *
 * This factory class is responsible for creating instances of matrix generators based on user input.
 * It determines the appropriate generator type (e.g., from a function or file) and constructs it accordingly.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class MatrixGeneratorFactory
{
public:
    MatrixGeneratorFactory(const std::string &inputName, const std::vector<std::string> &inputArgs) : inputName(inputName), inputArgs(inputArgs) {}; /**< Constructor */
    ~MatrixGeneratorFactory() {};                                                                                                                    /**< Destructor */
    /**
     * \brief Chooses and creates a matrix generator based on the input type.
     *
     * This method evaluates the input type (`inputName`) and delegates the creation
     * to either a function-based or file-based generator.
     *
     * \return A unique pointer to a matrix generator object.
     */
    std::unique_ptr<MatrixGenerator<T>> ChooseGenerator();

private:
    /**
     * \brief Creates a generator for matrix construction from a function.
     *
     * This helper method constructs a generator based on a mathematical function
     * (e.g., identity, Hilbert matrix), check that the user input is valid.
     *
     * \return A unique pointer to a function-based matrix generator.
     */
    std::unique_ptr<MatrixGeneratorFromFunction<T>> ChooseFunctionGenerator();

    /**
     * \brief Creates a generator for matrix construction from a file.
     *
     * This helper method constructs a generator that reads matrix data from a file.
     * The file type (e.g., CSV, TXT, MTX) is determined by the file extension and user input is checked.
     *
     * \return A unique pointer to a file-based matrix generator.
     */
    std::unique_ptr<MatrixGeneratorFromFile<T>> ChooseFileGenerator();

    const std::string &inputName;              /**< The input type for generator creation. */
    const std::vector<std::string> &inputArgs; /**< Arguments for the generator creation. */
};

#endif