#include <cmath>
#include <gtest/gtest.h>
#include "../src/MatrixGeneratorFromFunction.hpp"
#include <iostream>
#include <Eigen/Dense>

TEST(matrix_generator_from_function, generate_identity_matrix_float)
{
    std::vector<std::string> args = {"identity", "2", "2"};

    // Create the generator and generate the matrix
    MatrixGeneratorFromFunction<float> generator(args);
    auto matrix = generator.generate_matrix();

    // Define the expected matrix
    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> expected(2, 2);
    expected << 1.0, 0.0, 0.0, 1.0;

    ASSERT_TRUE(matrix != nullptr);
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected));                                                           // Compare matrices
    EXPECT_TRUE((std::is_same_v<typename std::remove_reference_t<decltype(*matrix)>::Scalar, float>)); // check type is float
}

TEST(matrix_generator_from_function, generate_hilbert_matrix_float)
{
    std::vector<std::string> args = {"hilbert", "3", "3"};

    // Create the generator and generate the matrix
    MatrixGeneratorFromFunction<float> generator(args);
    auto matrix = generator.generate_matrix();

    // Define the expected Hilbert matrix
    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << 1.0, 1.0 / 2.0, 1.0 / 3.0,
        1.0 / 2.0, 1.0 / 3.0, 1.0 / 4.0,
        1.0 / 3.0, 1.0 / 4.0, 1.0 / 5.0;

    ASSERT_TRUE(matrix != nullptr);
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-5));                                                     // Compare matrices with a tolerance
    EXPECT_TRUE((std::is_same_v<typename std::remove_reference_t<decltype(*matrix)>::Scalar, float>)); // check type is float
}