#include <cmath>
#include <gtest/gtest.h>
#include "constants.hpp"
#include "SolverFactory.hpp"
#include "PowerMethodSolver.hpp"
#include "InversePowerMethodSolver.hpp"
#include "QrMethodSolver.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <fstream>
#include <numeric>

using type_test = double;                                                    // Choose float or double: enable to avoid redundent testing
using MatrixTest = Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>; // For readability
using VectorTest = Eigen::Matrix<type_test, Eigen::Dynamic, 1>;              // For readability

// ********
// FIXTURES
// ********

// Fixture class: configuration for Identity Matrix
class IdentityMatrixTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        matrix = std::make_shared<MatrixTest>(MatrixTest::Identity(size, size));
    }
    std::shared_ptr<Matrix<type_test>> matrix;
    int maxIter = 1000;
    double tolerance = 1e-6;
    double shift = 0.0;
    int size = 3;
};

// Fixture class: configuration for Diagonal Matrix
class DiagonalMatrixTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        matrix = std::make_shared<MatrixTest>(size, size);
        Eigen::VectorXd diagonal(size);
        std::vector<type_test> values(size);
        std::iota(values.begin(), values.end(), 1.0);
        for (int i = 0; i < values.size(); ++i)
        {
            (*matrix)(i, i) = values[i];
        }
    }
    std::shared_ptr<Matrix<type_test>> matrix;
    int maxIter = 1000;
    double tolerance = 1e-6;
    double shift = 0.0;
    int size = 10;
};

// Fixture class: configuration for Hilbert Matrix
class HilbertMatrixTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        matrix = std::make_shared<MatrixTest>(size, size);
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                (*matrix)(i, j) = 1.0 / ((i + 1) + (j + 1) - 1.0); // 1-based indexing (i+1, j+1)
            }
        }
    }
    std::shared_ptr<Matrix<type_test>> matrix;
    int maxIter = 1000;
    double tolerance = 1e-12; // High tolerance for Hilbert because it is a very ill-conditioned matrix
    float shift = 0.0;
    int size = 50; // High number to make it very ill-conditioned and test the stability of the algorithm
};

// **********************
// IDENTITY MATRIX TESTS
// **********************

TEST_F(IdentityMatrixTest, PowerMethod)
{
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expected_eigenvalue = 1.0;
    ASSERT_NEAR(eigenvalues(0), expected_eigenvalue, tolerance * 10);
};

TEST_F(IdentityMatrixTest, InversePowerMethod)
{
    InversePowerMethodSolver<type_test> solver = InversePowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expected_eigenvalue = 1.0;
    ASSERT_NEAR(eigenvalues(0), expected_eigenvalue, tolerance * 10);
};

TEST_F(IdentityMatrixTest, QrMethod)
{
    QrMethodSolver<type_test> solver = QrMethodSolver<type_test>(tolerance, maxIter);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    VectorTest expected_eigenvalues(size);
    expected_eigenvalues.setOnes();
    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, tolerance * 10));
};

// **********************
// DIAGONAL MATRIX TESTS
// **********************

TEST_F(DiagonalMatrixTest, PowerMethod)
{
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expected_eigenvalue = size;
    ASSERT_NEAR(eigenvalues(0), expected_eigenvalue, tolerance * 10);
};

// Check with small shift => should return the highest eigenvalue
TEST_F(DiagonalMatrixTest, PowerMethodSmallShift)
{
    type_test new_shift = 1.0;
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, new_shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expected_eigenvalue = size;
    ASSERT_NEAR(eigenvalues(0), expected_eigenvalue, tolerance * 10);
};

// Check with big shift => should return lowest eigenvalue
TEST_F(DiagonalMatrixTest, PowerMethodBigSshift)
{
    type_test new_shift = size + 1;
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, new_shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expected_eigenvalue = 1.0;
    ASSERT_NEAR(eigenvalues(0), expected_eigenvalue, tolerance * 10);
};

TEST_F(DiagonalMatrixTest, InversePowerMethod)
{
    InversePowerMethodSolver<type_test> solver = InversePowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expected_eigenvalue = 1.0;
    ASSERT_NEAR(eigenvalues(0), expected_eigenvalue, tolerance * 10);
};

// Check with shift => should return eigenvalue closest to the shift
TEST_F(DiagonalMatrixTest, InversePowerMethodShift)
{
    type_test new_shift = 3.0;
    InversePowerMethodSolver<type_test> solver = InversePowerMethodSolver<type_test>(tolerance, maxIter, new_shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expected_eigenvalue = new_shift;
    ASSERT_NEAR(eigenvalues(0), expected_eigenvalue, tolerance * 10);
};

TEST_F(DiagonalMatrixTest, QrMethod)
{
    QrMethodSolver<type_test> solver = QrMethodSolver<type_test>(tolerance, maxIter);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    std::vector<type_test> values(size);
    std::iota(values.begin(), values.end(), 1.0);
    VectorTest expected_eigenvalues = Eigen::Map<VectorTest>(values.data(), size);
    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, tolerance * 10));
};

// ********************
// HILBERT MATRIX TESTS
// ********************

TEST_F(HilbertMatrixTest, PowerMethod)
{
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    Eigen::EigenSolver<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>> eigen_solver(*matrix);
    type_test expected_eigenvalue = eigen_solver.eigenvalues().real().maxCoeff();
    ASSERT_NEAR(eigenvalues(0), expected_eigenvalue, tolerance * 10);
};

TEST_F(HilbertMatrixTest, InversePowerMethod)
{
    InversePowerMethodSolver<type_test> solver = InversePowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    Eigen::EigenSolver<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>> eigen_solver(*matrix);
    type_test expected_eigenvalue = eigen_solver.eigenvalues().real().minCoeff();
    ASSERT_NEAR(eigenvalues(0), expected_eigenvalue, tolerance * 10);
};

TEST_F(HilbertMatrixTest, QrMethod)
{
    QrMethodSolver<type_test> solver = QrMethodSolver<type_test>(tolerance, maxIter);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    Eigen::EigenSolver<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>> eigen_solver(*matrix);
    VectorTest expected_eigenvalues = eigen_solver.eigenvalues().real();
    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, tolerance * 10));
};

// *****************************
// QR decomposition method tests
// *****************************

// Helper method to check if a matrix is upper triangular
bool is_upper_triangular(MatrixTest R, int size, type_test tolerance)
{
    bool is_upper_triangular = true;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (std::abs(R(i, j)) > tolerance)
            {
                is_upper_triangular = false;
                break;
            }
        }
    }
    return is_upper_triangular;
}

TEST_F(HilbertMatrixTest, QrDecomposition)
{
    // Initialize Q and R
    MatrixTest Q(size, size);
    MatrixTest R(size, size);

    // Create solver
    QrMethodSolver<type_test> solver = QrMethodSolver<type_test>(tolerance, maxIter);
    solver.SetMatrix(matrix);

    solver.QrDecomposition(*matrix, Q, R);

    // Test that R is upper triangular
    EXPECT_TRUE(is_upper_triangular(R, size, tolerance * 10));

    // Test that Q is orthogonal
    MatrixTest identity = Q.transpose() * Q;
    MatrixTest expected_identity = MatrixTest::Identity(size, size);
    EXPECT_TRUE(identity.isApprox(expected_identity, tolerance * 10));

    // Test the QR = *hilbert
    MatrixTest reconstructed_hilbert = Q * R;
    EXPECT_TRUE(reconstructed_hilbert.isApprox(*matrix, tolerance * 10));
}

TEST_F(IdentityMatrixTest, QrDecomposition)
{
    // Initialize Q and R
    MatrixTest Q(size, size);
    MatrixTest R(size, size);

    // Create solver
    QrMethodSolver<type_test> solver = QrMethodSolver<type_test>(tolerance, maxIter);
    solver.SetMatrix(matrix);
    solver.QrDecomposition(*matrix, Q, R);

    // Test that R is upper triangular
    EXPECT_TRUE(is_upper_triangular(R, size, tolerance * 10));

    // Test that Q is orthogonal
    MatrixTest identity = Q.transpose() * Q;
    MatrixTest expected_identity = MatrixTest::Identity(size, size);
    EXPECT_TRUE(identity.isApprox(expected_identity, tolerance * 10));

    // Test the QR = *hilbert
    MatrixTest reconstructed_hilbert = Q * R;
    EXPECT_TRUE(reconstructed_hilbert.isApprox(*matrix, tolerance * 10));
}