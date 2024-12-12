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

using type_test = double; // choose float or double: enable to avoid redundent testing

// ********
// FIXTURES
// ********

// Fixture for matrix generator from functions
class MatrixGeneratorFromFunctionTest : public ::testing::Test
{
protected:
    std::unique_ptr<MatrixGeneratorFromFunction<type_test>> generator;

    void initialize(const std::string &functionName, int rows, int cols)
    {
        auto function = std::make_unique<FunctionManager<type_test>>(functionName);
        generator = std::make_unique<MatrixGeneratorFromFunction<type_test>>(std::move(function), rows, cols);
    }
};

// Fixture for matrix generator from TXT file
class MatrixGeneratorFromFileTxtTest : public ::testing::Test
{
protected:
    std::unique_ptr<MatrixGeneratorFromFile<type_test>> generator;

    void initialize(const std::string &fileName)
    {
        auto fileReader = std::make_unique<FileReaderTXT<type_test>>(fileName);
        generator = std::make_unique<MatrixGeneratorFromFile<type_test>>(std::move(fileReader));
    }
};

// Fixture for matrix generator from CSV file
class MatrixGeneratorFromFileCsvTest : public ::testing::Test
{
protected:
    std::unique_ptr<MatrixGeneratorFromFile<type_test>> generator;

    void initialize(const std::string &fileName)
    {
        auto fileReader = std::make_unique<FileReaderCSV<type_test>>(fileName);
        generator = std::make_unique<MatrixGeneratorFromFile<type_test>>(std::move(fileReader));
    }
};

// Fixture for matrix generator from MTX file
class MatrixGeneratorFromFileMtxTest : public ::testing::Test
{
protected:
    std::unique_ptr<MatrixGeneratorFromFile<type_test>> generator;

    void initialize(const std::string &fileName)
    {
        auto fileReader = std::make_unique<FileReaderMTX<type_test>>(fileName);
        generator = std::make_unique<MatrixGeneratorFromFile<type_test>>(std::move(fileReader));
    }
};

// ********************************
// GENETATE MATRICES FROM FUNCTIONS
// ********************************

TEST_F(MatrixGeneratorFromFunctionTest, GenerateIdentityMatrix)
{
    initialize("identity", 2, 2);
    auto matrix = generator->GenerateMatrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(2, 2);
    expected << 1.0, 0.0, 0.0, 1.0;

    ASSERT_TRUE(matrix != nullptr);
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-6)); // Compare matrices
}

TEST_F(MatrixGeneratorFromFunctionTest, GenerateHilbertMatrix)
{
    initialize("hilbert", 3, 3);
    auto matrix = generator->GenerateMatrix();

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

TEST_F(MatrixGeneratorFromFileTxtTest, TxtFile)
{
    initialize("A.txt");
    auto matrix = generator->GenerateMatrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0;

    ASSERT_TRUE(matrix != nullptr); // Ensure matrix is not null
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-6)); // Compare matrices with a tolerance
}

TEST_F(MatrixGeneratorFromFileTxtTest, TxtFileEmpty)
{
    const std::string emptyFile = "empty.txt"; // Create a temporary empty file
    std::ofstream tempFile("../input/matrices/" + emptyFile);
    tempFile.close();
    initialize(emptyFile);

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove(("../input/matrices/" + emptyFile).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileTxtTest, TxtFileInvalid)
{
    const std::string invalidFile = "invalid_file.txt";
    std::ofstream tempFile("../input/matrices/" + invalidFile);
    tempFile << "1.0 2.0 3.0\n"
                "4.0 5.0 invalid\n" // invalid entry
                "7.0 8.0 9.0\n";
    tempFile.close();
    initialize(invalidFile);

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove(("../input/matrices/" + invalidFile).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileTxtTest, TxtFileInconsistentColumns)
{
    const std::string invalidFile = "inconsistent_columns.txt";
    std::ofstream tempFile("../input/matrices/" + invalidFile);
    tempFile << "1.0 2.0 3.0\n"
                "4.0 5.0\n" // less columns: inconsistent
                "7.0 8.0 9.0\n";
    tempFile.close();
    initialize(invalidFile);

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove(("../input/matrices/" + invalidFile).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileTxtTest, TxtNoFile)
{
    initialize("invalid_file.txt");

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove("../input/matrices/invalid_file.txt"); // Clean up the temporary file
}

// ********************************
// GENETATE MATRICES FROM CSV FILES
// ********************************

TEST_F(MatrixGeneratorFromFileCsvTest, CsvFile)
{
    initialize("A.csv");
    auto matrix = generator->GenerateMatrix();

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

TEST_F(MatrixGeneratorFromFileCsvTest, CsvFileEmpty)
{
    // Create a temporary empty file
    const std::string emptyFile = "empty.csv";
    std::ofstream tempFile("../input/matrices/" + emptyFile);
    tempFile.close();
    initialize(emptyFile);

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove(("../input/matrices/" + emptyFile).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileCsvTest, CsvFileInvalid)
{
    const std::string invalidFile = "invalid_file.csv";
    std::ofstream tempFile("../input/matrices/" + invalidFile);
    tempFile << "1.0, 2.0, 3.0\n"
                "4.0, 5.0, invalid\n" // invalid entry
                "7.0, 8.0, 9.0\n";
    tempFile.close();
    initialize(invalidFile);

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove(("../input/matrices/" + invalidFile).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileCsvTest, CsvFileInconsistentColumns)
{
    const std::string invalidFile = "inconsistent_columns.csv";
    std::ofstream tempFile("../input/matrices/" + invalidFile);
    tempFile << "1.0, 2.0, 3.0\n"
                "4.0, 5.0\n" // less columns: inconsistent
                "7.0, 8.0, 9.0\n";
    tempFile.close();
    initialize(invalidFile);

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove(("../input/matrices/" + invalidFile).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileCsvTest, CsvNoFile)
{
    initialize("invalid_file.csv");

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove("../input/matrices/invalid_file.csv"); // Clean up the temporary file
}

// ********************************
// GENERATE MATRICES FROM MTX FILES
// ********************************

TEST_F(MatrixGeneratorFromFileMtxTest, MtxFile)
{
    initialize("B.mtx");
    auto matrix = generator->GenerateMatrix();

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

TEST_F(MatrixGeneratorFromFileMtxTest, MtxFileEmpty)
{
    // Create a temporary empty file
    const std::string emptyFile = "empty.mtx";
    std::ofstream tempFile("../input/matrices/" + emptyFile);
    tempFile.close();
    initialize(emptyFile);

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove(("../input/matrices/" + emptyFile).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileMtxTest, MtxFileInvalid)
{
    const std::string invalidFile = "invalid_file.mtx";
    std::ofstream tempFile("../input/matrices/" + invalidFile);
    tempFile << "% this is a comment\n"
                "% this is a second line of comments\n"
                "3 3 6\n"
                "1 1 invalid_entry"; // invalid_entry
    tempFile.close();
    initialize(invalidFile);

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove(("../input/matrices/" + invalidFile).c_str()); // Clean up the temporary file
}

TEST_F(MatrixGeneratorFromFileMtxTest, MtxNoFile)
{
    initialize("invalid_file.mtx");

    EXPECT_THROW(generator->GenerateMatrix(), FileException);

    std::remove("../input/matrices/invalid_file.mtx"); // Clean up the temporary file
}