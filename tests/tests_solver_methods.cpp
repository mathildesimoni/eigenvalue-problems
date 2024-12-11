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

using type_test = double;

 // TODO: 
 // - EXPECT_THROW for square matrix test
 // - test SolverFactory
 //     - method_name
 //     - method_args

 
// Base fixture class for solver tests
class SolverTest : public ::testing::Test {
protected:
    std::shared_ptr<Matrix<type_test>> matrix;
    std::unique_ptr<AbstractIterativeSolver<type_test>> solver;

    virtual void define_matrix() = 0;

    void initializeSolver(const std::string &method_name, const std::vector<std::string> &method_args) {
        define_matrix();
        SolverFactory<type_test> solver_factory(method_name, method_args);
        solver = solver_factory.choose_solver();
        solver->SetMatrix(matrix);
    }
};

// Fixture for identity matrix tests
class IdentityMatrixTest : public SolverTest {
protected:
    void define_matrix() override {
        matrix = std::make_shared<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>>(3, 3);
        *matrix << 1.0, 0.0, 0.0,
                   0.0, 1.0, 0.0,
                   0.0, 0.0, 1.0;
    }
};

// Fixture for Hilbert matrix tests
class HilbertMatrixTest : public SolverTest {
protected:
    void define_matrix() override {
        matrix = std::make_shared<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>>(3, 3);
        *matrix << 1.0, 1.0 / 2.0, 1.0 / 3.0,
                   1.0 / 2.0, 1.0 / 3.0, 1.0 / 4.0,
                   1.0 / 3.0, 1.0 / 4.0, 1.0 / 5.0;
    }
};

// **********************
// IDENTITY MATRIX TESTS
// **********************

TEST_F(IdentityMatrixTest, PowerMethodSolver) {
    initializeSolver("power_method", {"1e-6", "1000", "0.0"});
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver->FindEigenvalues();
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(1);
    expected_eigenvalues << 1.0;
    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-3));
}

TEST_F(IdentityMatrixTest, InversePowerMethodSolver) {
    initializeSolver("inverse_power_method", {"1e-6", "1000", "0.0"});
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver->FindEigenvalues();
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(1);
    expected_eigenvalues << 1.0;
    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-3));
}

TEST_F(IdentityMatrixTest, QRMethodSolver) {
    initializeSolver("QR_method", {"1e-6", "1000"});
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver->FindEigenvalues();
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(3);
    expected_eigenvalues << 1.0, 1.0, 1.0;
    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-3));
}

// **********************
// HILBERT MATRIX TESTS
// **********************

TEST_F(HilbertMatrixTest, PowerMethodSolver) {
    initializeSolver("power_method", {"1e-6", "1000", "0.0"});
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver->FindEigenvalues();
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(1);
    expected_eigenvalues << 1.40832;
    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-3));
}

TEST_F(HilbertMatrixTest, InversePowerMethodSolver) {
    initializeSolver("inverse_power_method", {"1e-6", "1000", "0.0"});
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver->FindEigenvalues();
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(1);
    expected_eigenvalues << 0.00268734;
    std::cout << "** computed eigenvalue: " << eigenvalues << std::endl;
    std::cout << "** expected eigenvalue: " << expected_eigenvalues << std::endl;
    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-6));
}

TEST_F(HilbertMatrixTest, QrMethodSolver) {
    initializeSolver("QR_method", {"1e-6", "1000"});
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver->FindEigenvalues();
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(3);
    expected_eigenvalues << 1.40832, 0.122327, 0.00268734;
    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-6));
}

TEST_F(HilbertMatrixTest, QrDecomposition) {
    initializeSolver("QR_method", {"1e-6", "1000", "0.0"});
    int n = (*matrix).rows();

    // Initialize Q and R
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> Q(n, n);
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> R(n, n);

    // Check if the solver supports QR decomposition
    auto qr_solver = dynamic_cast<QrMethodSolver<type_test>*>(solver.get());
    ASSERT_NE(qr_solver, nullptr) << "Solver does not support QR decomposition";

    qr_solver->QrDecomposition(*matrix, Q, R);

    // Test that R is upper diagonal
    bool is_upper_triangular = true;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (std::abs(R(i, j)) > 1e-6)
            {
                is_upper_triangular = false;
                break;
            }
        }
    }
    EXPECT_TRUE(is_upper_triangular);

    // Test that Q is orthogonal
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> identity = Q.transpose() * Q;
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected_identity = Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>::Identity(n, n);
    EXPECT_TRUE(identity.isApprox(expected_identity, 1e-6));

    // Test the QR = *hilbert
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> reconstructed_hilbert = Q * R;
    EXPECT_TRUE(reconstructed_hilbert.isApprox(*matrix, 1e-6));
}

TEST_F(IdentityMatrixTest, QrDecomposition)
{
    initializeSolver("QR_method", {"1e-6", "1000", "0.0"});
    int n = (*matrix).rows();

    // Initialize Q and R
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> Q(n, n);
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> R(n, n);

    // Check if the solver supports QR decomposition
    auto qr_solver = dynamic_cast<QrMethodSolver<type_test>*>(solver.get());
    ASSERT_NE(qr_solver, nullptr) << "Solver does not support QR decomposition";

    qr_solver->QrDecomposition(*matrix, Q, R);

    // Test that R is upper diagonal
    bool is_upper_triangular = true;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (std::abs(R(i, j)) > 1e-6)
            {
                is_upper_triangular = false;
                break;
            }
        }
    }
    EXPECT_TRUE(is_upper_triangular);

    // Test that Q is orthogonal
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> identity_reformed = Q.transpose() * Q;
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected_identity = Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>::Identity(n, n);
    EXPECT_TRUE(identity_reformed.isApprox(expected_identity, 1e-6));

    // Test the QR = *hilbert
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> reconstructed_identity = Q * R;
    EXPECT_TRUE(reconstructed_identity.isApprox(*matrix, 1e-6));
}