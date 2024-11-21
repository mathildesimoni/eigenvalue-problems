#include <iostream>
#include <Eigen/Dense>
#include "test_class.hpp"

int main(int argc, char *argv[])
{

    // Command line arguments
    std::cout << "Number of command line arguments = " << argc << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << "Argument " << i << " = " << argv[i] << std::endl;
    }

    // Tryout for Eigen library
    Eigen::MatrixXd m(3, 3);
    std::cout << "nb_rows: " << m.rows() << std::endl;
    std::cout << "nb_cols: " << m.cols() << std::endl;
    std::cout << "size: " << m.size() << std::endl;
    std::cout << "m = " << m << std::endl;
    std::cout << "m.T = " << m.transpose() << std::endl;

    // Test include test_class
    int test_return_value = foo();
    std::cout << "Return value test: " << test_return_value << std::endl;

    return 0;
}