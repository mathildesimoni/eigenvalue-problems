#ifndef __FUNCTION_MANAGER__HH__
#define __FUNCTION_MANAGER__HH__

#include <iostream>
#include <string>

template <typename T>
class FunctionManager
{
public:
    FunctionManager(const std::string &function_name);
    ~FunctionManager();
    T operator()(int row, int col);

private:
    std::function<T(int, int)> selected_function;
    T identity_matrix(int row, int col);
    T hilbert_matrix(int row, int col);
};

#endif