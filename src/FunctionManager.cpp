#include "FunctionManager.hpp"
#include <iostream>
#include <string>

template <typename T>
FunctionManager<T>::FunctionManager(const std::string &function_name)
{
    if (function_name == "identity")
        selected_function = [this](int row, int col)
        { return FunctionManager::identity_matrix(row, col); };
    else if (function_name == "hilbert")
        selected_function = [this](int row, int col)
        { return FunctionManager::hilbert_matrix(row, col); };
    else
        throw std::invalid_argument("Unknown function name: " + function_name);
}

template <typename T>
FunctionManager<T>::~FunctionManager() {}

template <typename T>
T FunctionManager<T>::operator()(int row, int col)
{
    if (!selected_function)
        throw std::runtime_error("No function selected");
    return selected_function(row, col);
}

template <typename T>
T FunctionManager<T>::identity_matrix(int row, int col)
{
    T return_value = static_cast<T>(0);
    if (row == col)
        return_value = static_cast<T>(1);
    return return_value;
}

template <typename T>
T FunctionManager<T>::hilbert_matrix(int row, int col)
{
    T return_value = static_cast<T>(1) / ((row + 1) + (col + 1) + 1); // since row and col are 0-indexed
    return return_value;
}

// Explicit instantiations
template class FunctionManager<float>;
template class FunctionManager<double>;