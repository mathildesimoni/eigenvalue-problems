#ifndef __OUTPUT_GENERATOR__HH__
#define __OUTPUT_GENERATOR__HH__

#include <iostream>
#include <functional>
#include <Eigen/Dense>

template <typename T>
class OutputGenerator
{
public:
    OutputGenerator(const std::string &output_type, const std::string &output_arg, Eigen::Matrix<T, Eigen::Dynamic, 1> &data);
    ~OutputGenerator() {};
    void generate_output();
    void write_in_file();
    void print_to_terminal();

private:
    std::string output_arg;
    std::function<void()> output_function;
    Eigen::Matrix<T, Eigen::Dynamic, 1> eigenvalues;
};

#endif