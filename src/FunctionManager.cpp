#include <iostream>
#include <string>

#include "FunctionManager.hpp"

template <typename T>
FunctionManager<T>::FunctionManager(const std::string &functionName)
{
    if (functionName == "identity")
        selectedFunction = [this](int row, int col)
        { return FunctionManager::IdentityMatrix(row, col); };
    else if (functionName == "hilbert")
        selectedFunction = [this](int row, int col)
        { return FunctionManager::HilbertMatrix(row, col); };
    else
        throw std::invalid_argument("Unknown function name (" + functionName + ") during matrix initialization");
}

template <typename T>
FunctionManager<T>::~FunctionManager() {}

template <typename T>
T FunctionManager<T>::operator()(int row, int col)
{
    if (!selectedFunction)
        throw std::runtime_error("No function selected (FunctionManager)");
    return selectedFunction(row, col);
}

template <typename T>
T FunctionManager<T>::IdentityMatrix(int row, int col)
{
    T returnValue = static_cast<T>(0.0);
    if (row == col)
        returnValue = static_cast<T>(1.0);
    return returnValue;
}

template <typename T>
T FunctionManager<T>::HilbertMatrix(int row, int col)
{
    T returnValue = static_cast<T>(1.0) / ((row + 1) + (col + 1) - 1.0); // Since row and col are 0-indexed
    return returnValue;
}

// Explicit instantiations
template class FunctionManager<float>;
template class FunctionManager<double>;