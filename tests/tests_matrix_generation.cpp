#include <cmath>
#include <gtest/gtest.h>
#include "MatrixGeneratorFromFunction.hpp"
#include "MatrixGeneratorFromFile.hpp"
#include "FunctionManager.hpp"
#include "FileReader.hpp"
#include "FileReaderTXT.hpp"
#include "FileReaderCSV.hpp"
#include "FileReaderMTX.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <fstream>
#include <iostream>

using type_test = float; // choose float or double: enable to avoid redundent testing

// ********
// FIXTURES
// ********
// Fixture for matrix generator from functions
class MatrixGeneratorFromFunctionTest : public ::testing::Test
{
protected:
    std::unique_ptr<MatrixGeneratorFromFunction<type_test>> generator;

    void initialize(const std::string &function_name, int rows, int cols)
    {
        auto function = std::make_unique<FunctionManager<type_test>>(function_name);
        generator = std::make_unique<MatrixGeneratorFromFunction<type_test>>(std::move(function), rows, cols);
    }
};

// Fixture for matrix generator from TXT file
class MatrixGeneratorFromFileTxtTest : public ::testing::Test
{
protected:
    std::unique_ptr<MatrixGeneratorFromFile<type_test>> generator;

    void initialize(const std::string &file_name)
    {
        auto file_reader = std::make_unique<FileReaderTXT<type_test>>(file_name);
        generator = std::make_unique<MatrixGeneratorFromFile<type_test>>(std::move(file_reader));
    }
};

// Fixture for matrix generator from CSV file
class MatrixGeneratorFromFileCsvTest : public ::testing::Test
{
protected:
    std::unique_ptr<MatrixGeneratorFromFile<type_test>> generator;

    void initialize(const std::string &file_name)
    {
        auto file_reader = std::make_unique<FileReaderCSV<type_test>>(file_name);
        generator = std::make_unique<MatrixGeneratorFromFile<type_test>>(std::move(file_reader));
    }
};

// Fixture for matrix generator from MTX file
class MatrixGeneratorFromFileMtxTest : public ::testing::Test
{
protected:
    std::unique_ptr<MatrixGeneratorFromFile<type_test>> generator;

    void initialize(const std::string &file_name)
    {
        auto file_reader = std::make_unique<FileReaderMTX<type_test>>(file_name);
        generator = std::make_unique<MatrixGeneratorFromFile<type_test>>(std::move(file_reader));
    }
};

// ********************************
// GENETATE MATRICES FROM FUNCTIONS
// ********************************

TEST_F(MatrixGeneratorFromFunctionTest, generate_identity_matrix)

{
    initialize("identity", 2, 2);
    auto matrix = generator->generate_matrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(2, 2);
    expected << 1.0, 0.0, 0.0, 1.0;

    ASSERT_TRUE(matrix != nullptr);
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected));                                                               // Compare matrices
    EXPECT_TRUE((std::is_same_v<typename std::remove_reference_t<decltype(*matrix)>::Scalar, type_test>)); // check type
}

TEST_F(MatrixGeneratorFromFunctionTest, generate_hilbert_matrix)
{
    initialize("hilbert", 3, 3);
    auto matrix = generator->generate_matrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << 1.0, 1.0 / 2.0, 1.0 / 3.0,
        1.0 / 2.0, 1.0 / 3.0, 1.0 / 4.0,
        1.0 / 3.0, 1.0 / 4.0, 1.0 / 5.0;

    ASSERT_TRUE(matrix != nullptr);
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-5)); // Compare matrices with a tolerance
}

// ********************************
// GENETATE MATRICES FROM TXT FILES
// ********************************

TEST_F(MatrixGeneratorFromFileTxtTest, txt_file)
{
    initialize("A.txt");
    auto matrix = generator->generate_matrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0;

    ASSERT_TRUE(matrix != nullptr); // Ensure matrix is not null
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-5)); // Compare matrices with a tolerance
}

TEST_F(MatrixGeneratorFromFileTxtTest, txt_empty)
{
    const std::string empty_file = "empty.txt"; // Create a temporary empty file
    std::ofstream temp_file("../input/matrices/" + empty_file);
    temp_file.close();
    initialize(empty_file);

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove(("../input/matrices/" + empty_file).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileTxtTest, txt_invalid)
{
    const std::string invalid_file = "invalid_file.txt";
    std::ofstream temp_file("../input/matrices/" + invalid_file);
    temp_file << "1.0 2.0 3.0\n"
                 "4.0 5.0 invalid\n" // invalid entry
                 "7.0 8.0 9.0\n";
    temp_file.close();
    initialize(invalid_file);

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove(("../input/matrices/" + invalid_file).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileTxtTest, txt_inconsistent_columns)
{
    const std::string invalid_file = "inconsistent_columns.txt";
    std::ofstream temp_file("../input/matrices/" + invalid_file);
    temp_file << "1.0 2.0 3.0\n"
                 "4.0 5.0\n" // less columns: inconsistent
                 "7.0 8.0 9.0\n";
    temp_file.close();
    initialize(invalid_file);

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove(("../input/matrices/" + invalid_file).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileTxtTest, txt_no_file)
{
    initialize("invalid_file.txt");

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove("../input/matrices/invalid_file.txt"); // Clean up the temporary file
}

// ********************************
// GENETATE MATRICES FROM CSV FILES
// ********************************

TEST_F(MatrixGeneratorFromFileCsvTest, csv_file)
{
    initialize("A.csv");
    auto matrix = generator->generate_matrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0;

    ASSERT_TRUE(matrix != nullptr); // Ensure matrix is not null
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-5)); // Compare matrices with a tolerance
}

TEST_F(MatrixGeneratorFromFileCsvTest, csv_empty)
{
    // Create a temporary empty file
    const std::string empty_file = "empty.csv";
    std::ofstream temp_file("../input/matrices/" + empty_file);
    temp_file.close();
    initialize(empty_file);

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove(("../input/matrices/" + empty_file).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileCsvTest, csv_invalid)
{
    const std::string invalid_file = "invalid_file.csv";
    std::ofstream temp_file("../input/matrices/" + invalid_file);
    temp_file << "1.0, 2.0, 3.0\n"
                 "4.0, 5.0, invalid\n" // invalid entry
                 "7.0, 8.0, 9.0\n";
    temp_file.close();
    initialize(invalid_file);

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove(("../input/matrices/" + invalid_file).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileCsvTest, csv_inconsistent_columns)
{
    const std::string invalid_file = "inconsistent_columns.csv";
    std::ofstream temp_file("../input/matrices/" + invalid_file);
    temp_file << "1.0, 2.0, 3.0\n"
                 "4.0, 5.0\n" // less columns: inconsistent
                 "7.0, 8.0, 9.0\n";
    temp_file.close();
    initialize(invalid_file);

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove(("../input/matrices/" + invalid_file).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileCsvTest, csv_no_file)
{
    initialize("invalid_file.csv");

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove("../input/matrices/invalid_file.csv"); // Clean up the temporary file
}

// ********************************
// GENETATE MATRICES FROM MTX FILES
// ********************************

TEST_F(MatrixGeneratorFromFileMtxTest, mtx_file)
{
    initialize("B.mtx");
    auto matrix = generator->generate_matrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << 1.5, 0.0, 0.0,
        0.0, 2.5, 0.0,
        0.0, 0.0, 3.5;

    ASSERT_TRUE(matrix != nullptr); // Ensure matrix is not null
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-5)); // Compare matrices with a tolerance
}

TEST_F(MatrixGeneratorFromFileMtxTest, mtx_empty)
{
    // Create a temporary empty file
    const std::string empty_file = "empty.mtx";
    std::ofstream temp_file("../input/matrices/" + empty_file);
    temp_file.close();
    initialize(empty_file);

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove(("../input/matrices/" + empty_file).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileMtxTest, mtx_invalid)
{
    const std::string invalid_file = "invalid_file.mtx";
    std::ofstream temp_file("../input/matrices/" + invalid_file);
    temp_file << "% this is a comment\n"
                 "% this is a second line of comments\n"
                 "3 3 6\n"
                 "1 1 invalid_entry"; // invalid_entry
    temp_file.close();
    initialize(invalid_file);

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove(("../input/matrices/" + invalid_file).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileMtxTest, mtx_no_file)
{
    initialize("invalid_file.mtx");

    EXPECT_THROW(generator->generate_matrix(), std::runtime_error);

    std::remove("../input/matrices/invalid_file.mtx"); // Clean up the temporary file
}