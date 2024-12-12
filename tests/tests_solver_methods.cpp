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
    double tolerance = 1e-10;
    double shift = 0.0;
    int size = 3;
};

// Fixture class: configuration for Diagonal Matrix
class DiagonalMatrixTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        matrix = std::make_shared<MatrixTest>(MatrixTest::Zero(size, size));
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
    double tolerance = 1e-10;
    double shift = 0.0;
    int size = 20;
};

// Fixture class: configuration for Hilbert Matrix
class HilbertMatrixTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        matrix = std::make_shared<MatrixTest>(MatrixTest::Zero(size, size));
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                (*matrix)(i, j) = 1.0 / ((i + 1.0) + (j + 1.0) - 1.0); // 1-based indexing (i+1, j+1)
            }
        }
    }
    std::shared_ptr<Matrix<type_test>> matrix;
    int maxIter = 1000;
    double tolerance = 1e-10;
    float shift = 0.0;
    int size = 5;
};

// Fixture class: configuration for larger Hilbert Matrix
class LargeHilbertMatrixTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        matrix = std::make_shared<MatrixTest>(MatrixTest::Zero(size, size));
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                (*matrix)(i, j) = 1.0 / ((i + 1.0) + (j + 1.0) - 1.0); // 1-based indexing (i+1, j+1)
            }
        }
    }
    std::shared_ptr<Matrix<type_test>> matrix;
    int maxIter = 1000;
    double tolerance = 1e-10;
    float shift = 0.0;
    int size = 20;
};

// **********************
// IDENTITY MATRIX TESTS
// **********************

TEST_F(IdentityMatrixTest, PowerMethod)
{
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expectedEigenvalue = 1.0;
    ASSERT_NEAR(eigenvalues(0), expectedEigenvalue, 1e-6);
};

TEST_F(IdentityMatrixTest, InversePowerMethod)
{
    InversePowerMethodSolver<type_test> solver = InversePowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expectedEigenvalue = 1.0;
    ASSERT_NEAR(eigenvalues(0), expectedEigenvalue, 1e-6);
};

TEST_F(IdentityMatrixTest, QrMethod)
{
    QrMethodSolver<type_test> solver = QrMethodSolver<type_test>(tolerance, maxIter);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    VectorTest expectedEigenvalues(size);
    expectedEigenvalues.setOnes();
    EXPECT_TRUE(eigenvalues.isApprox(expectedEigenvalues, 1e-6));
};

// **********************
// DIAGONAL MATRIX TESTS
// **********************

TEST_F(DiagonalMatrixTest, PowerMethod)
{
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expectedEigenvalue = size;
    ASSERT_NEAR(eigenvalues(0), expectedEigenvalue, 1e-6);
};

// Check with small shift => should return the highest eigenvalue
TEST_F(DiagonalMatrixTest, PowerMethodSmallShift)
{
    type_test newShift = 1.0;
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, newShift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expectedEigenvalue = size;
    ASSERT_NEAR(eigenvalues(0), expectedEigenvalue, 1e-6);
};

// Check with big shift => should return lowest eigenvalue
TEST_F(DiagonalMatrixTest, PowerMethodBigSshift)
{
    type_test newShift = size + 1;
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, newShift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expectedEigenvalue = 1.0;
    ASSERT_NEAR(eigenvalues(0), expectedEigenvalue, 1e-6);
};

TEST_F(DiagonalMatrixTest, InversePowerMethod)
{
    InversePowerMethodSolver<type_test> solver = InversePowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expectedEigenvalue = 1.0;
    ASSERT_NEAR(eigenvalues(0), expectedEigenvalue, 1e-6);
};

// Check with shift => should return eigenvalue closest to the shift
TEST_F(DiagonalMatrixTest, InversePowerMethodShift)
{
    type_test newShift = 3.0;
    InversePowerMethodSolver<type_test> solver = InversePowerMethodSolver<type_test>(tolerance, maxIter, newShift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    type_test expectedEigenvalue = newShift;
    ASSERT_NEAR(eigenvalues(0), expectedEigenvalue, 1e-6);
};

TEST_F(DiagonalMatrixTest, QrMethod)
{
    QrMethodSolver<type_test> solver = QrMethodSolver<type_test>(tolerance, maxIter);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    std::vector<type_test> values(size);
    std::iota(values.begin(), values.end(), 1.0);
    VectorTest expectedEigenvalues = Eigen::Map<VectorTest>(values.data(), size);
    EXPECT_TRUE(eigenvalues.isApprox(expectedEigenvalues, 1e-6));
};

// ********************
// HILBERT MATRIX TESTS
// ********************

TEST_F(HilbertMatrixTest, PowerMethod)
{
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    Eigen::EigenSolver<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>> eigenSolver(*matrix);
    type_test expectedEigenvalue = eigenSolver.eigenvalues().real().maxCoeff();
    ASSERT_NEAR(eigenvalues(0), expectedEigenvalue, 1e-6);
};

TEST_F(HilbertMatrixTest, InversePowerMethod)
{
    InversePowerMethodSolver<type_test> solver = InversePowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    Eigen::EigenSolver<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>> eigenSolver(*matrix);
    type_test expectedEigenvalue = eigenSolver.eigenvalues().real().minCoeff();

    ASSERT_NEAR(eigenvalues(0), expectedEigenvalue, 1e-6);
};

TEST_F(HilbertMatrixTest, QrMethod)
{
    QrMethodSolver<type_test> solver = QrMethodSolver<type_test>(tolerance, maxIter);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    Eigen::EigenSolver<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>> eigenSolver(*matrix);
    VectorTest expectedEigenvalues = eigenSolver.eigenvalues().real();
    EXPECT_TRUE(eigenvalues.isApprox(expectedEigenvalues, 1e-6));
};

// ********************
// LARGE HILBERT MATRIX TESTS
// ********************

TEST_F(LargeHilbertMatrixTest, PowerMethod)
{
    PowerMethodSolver<type_test> solver = PowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    Eigen::EigenSolver<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>> eigenSolver(*matrix);
    type_test expectedEigenvalue = eigenSolver.eigenvalues().real().maxCoeff();
    ASSERT_NEAR(eigenvalues(0), expectedEigenvalue, 1e-6);
};

TEST_F(LargeHilbertMatrixTest, InversePowerMethod)
{
    InversePowerMethodSolver<type_test> solver = InversePowerMethodSolver<type_test>(tolerance, maxIter, shift);
    solver.SetMatrix(matrix);

    Eigen::EigenSolver<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>> eigenSolver(*matrix);
    type_test expectedEigenvalue = eigenSolver.eigenvalues().real().minCoeff();

    // The matrix is very badly conditioned, the linear solver is expected to throw an error
    ASSERT_THROW(solver.FindEigenvalues(), SolverException);
};

TEST_F(LargeHilbertMatrixTest, QrMethod)
{
    QrMethodSolver<type_test> solver = QrMethodSolver<type_test>(tolerance, maxIter);
    solver.SetMatrix(matrix);
    VectorTest eigenvalues = solver.FindEigenvalues();

    Eigen::EigenSolver<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>> eigenSolver(*matrix);
    VectorTest expectedEigenvalues = eigenSolver.eigenvalues().real();
    EXPECT_TRUE(eigenvalues.isApprox(expectedEigenvalues, 1e-6));
};

// *****************************
// QR decomposition method tests
// *****************************

// Helper method to check if a matrix is upper triangular
bool IsUpperTriangular(MatrixTest R, int size, type_test tolerance)
{
    bool isUpperTriangular = true;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (std::abs(R(i, j)) > tolerance)
            {
                isUpperTriangular = false;
                break;
            }
        }
    }
    return isUpperTriangular;
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
    EXPECT_TRUE(IsUpperTriangular(R, size, 1e-6));

    // Test that Q is orthogonal
    MatrixTest identity = Q.transpose() * Q;
    MatrixTest expectedQuantity = MatrixTest::Identity(size, size);
    EXPECT_TRUE(identity.isApprox(expectedQuantity, 1e-6));

    // Test the QR = *hilbert
    MatrixTest reconstructedHilbert = Q * R;
    EXPECT_TRUE(reconstructedHilbert.isApprox(*matrix, 1e-6));
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
    EXPECT_TRUE(IsUpperTriangular(R, size, 1e-6));

    // Test that Q is orthogonal
    MatrixTest identity = Q.transpose() * Q;
    MatrixTest expectedQuantity = MatrixTest::Identity(size, size);
    EXPECT_TRUE(identity.isApprox(expectedQuantity, 1e-6));

    // Test the QR = *identity
    MatrixTest reconstructedIdentity = Q * R;
    EXPECT_TRUE(reconstructedIdentity.isApprox(*matrix, 1e-6));
}

TEST_F(DiagonalMatrixTest, QrDecomposition)
{
    // Initialize Q and R
    MatrixTest Q(size, size);
    MatrixTest R(size, size);

    // Create solver
    QrMethodSolver<type_test> solver = QrMethodSolver<type_test>(tolerance, maxIter);
    solver.SetMatrix(matrix);
    solver.QrDecomposition(*matrix, Q, R);

    // Test that R is upper triangular
    EXPECT_TRUE(IsUpperTriangular(R, size, 1e-6));

    // Test that Q is orthogonal
    MatrixTest identity = Q.transpose() * Q;
    MatrixTest expectedQuantity = MatrixTest::Identity(size, size);
    EXPECT_TRUE(identity.isApprox(expectedQuantity, 1e-6));

    // Test the QR = *diagonal
    MatrixTest reconstructedDiagonal = Q * R;
    EXPECT_TRUE(reconstructedDiagonal.isApprox(*matrix, 1e-6));
}