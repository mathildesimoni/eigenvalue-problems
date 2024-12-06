#include <cmath>
#include <gtest/gtest.h>
#include "../src/PowerMethodSolver.hpp"
#include "../src/InversePowerMethodSolver.hpp"
#include "../src/QrMethodSolver.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <fstream>

using type_test = float;

TEST(power_method_solver, identity_matrix)
{   
    auto identity = std::make_shared<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>>(3, 3);
    *identity << 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0;

    // Instantiate solver
    PowerMethodSolver<type_test> solver;
    solver.SetTolerance(1e-6);
    solver.SetMaxIter(1000);
    solver.SetShift(0.0);
    solver.SetMatrix(identity);

    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver.FindEigenvalues();  

    // Define expected eigenvalues
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(1);
    expected_eigenvalues << 1.0;

    // ASSERT_TRUE(eigenvalues != nullptr);
    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-6));
}

TEST(inverse_power_method_solver, identity_matrix){
    
    auto identity = std::make_shared<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>>(3, 3);
    *identity << 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0;

    // Instantiate solver
    PowerMethodSolver<type_test> solver;
    solver.SetTolerance(1e-6);
    solver.SetMaxIter(1000);
    solver.SetShift(0.0);
    solver.SetMatrix(identity);

    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver.FindEigenvalues();  

    // Define expected eigenvalues
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(1);
    expected_eigenvalues << 1.0;

    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-6));
}

TEST(qr_method_solver, identity_matrix){

    auto identity = std::make_shared<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>>(3, 3);
    *identity << 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0;

    // Instantiate solver
    PowerMethodSolver<type_test> solver;
    solver.SetTolerance(1e-6);
    solver.SetMaxIter(1000);
    solver.SetMatrix(identity);

    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver.FindEigenvalues();  

    // Define expected eigenvalues
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(5);
    expected_eigenvalues <<  1.0, 1.0, 1.0;

    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-6));
}

TEST(power_method_solver, hilbert_matrix){

    auto hilbert = std::make_shared<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>>(3, 3);
    *hilbert << 1.0, 1.0 / 2.0, 1.0 / 3.0,
        1.0 / 2.0, 1.0 / 3.0, 1.0 / 4.0,
        1.0 / 3.0, 1.0 / 4.0, 1.0 / 5.0;

    // Instantiate solver
    PowerMethodSolver<type_test> solver;
    solver.SetTolerance(1e-6);
    solver.SetMaxIter(1000);
    solver.SetShift(0.0);
    solver.SetMatrix(hilbert);

    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver.FindEigenvalues();  
    // Define expected eigenvalues
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(1);
    expected_eigenvalues << 1.40832;

    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-6));
}

TEST(inverse_power_method_solver, hilbert_matrix){

    auto hilbert = std::make_shared<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>>(3, 3);
    *hilbert << 1.0, 1.0 / 2.0, 1.0 / 3.0,
        1.0 / 2.0, 1.0 / 3.0, 1.0 / 4.0,
        1.0 / 3.0, 1.0 / 4.0, 1.0 / 5.0;

    // Instantiate solver
    PowerMethodSolver<type_test> solver;
    solver.SetTolerance(1e-6);
    solver.SetMaxIter(1000);
    solver.SetShift(0.0);
    solver.SetMatrix(hilbert);

    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver.FindEigenvalues();  

    // Define expected eigenvalues
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(1);
    expected_eigenvalues << 1.40832;

    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-6));
}

TEST(qr_method_solver, hilbert_matrix){

    auto hilbert = std::make_shared<Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic>>(3, 3);
    *hilbert << 1.0, 1.0 / 2.0, 1.0 / 3.0,
        1.0 / 2.0, 1.0 / 3.0, 1.0 / 4.0,
        1.0 / 3.0, 1.0 / 4.0, 1.0 / 5.0;
    
    // Instantiate solver
    PowerMethodSolver<type_test> solver;
    solver.SetTolerance(1e-6);
    solver.SetMaxIter(1000);
    solver.SetMatrix(hilbert);

    Eigen::Matrix<type_test, Eigen::Dynamic, 1> eigenvalues = solver.FindEigenvalues();  

    // Define expected eigenvalues
    Eigen::Matrix<type_test, Eigen::Dynamic, 1> expected_eigenvalues(5);
    expected_eigenvalues << 1.40832, 0.122327, 0.002687;

    EXPECT_TRUE(eigenvalues.isApprox(expected_eigenvalues, 1e-6));
}

// EXPECT_THROW for square matrix test