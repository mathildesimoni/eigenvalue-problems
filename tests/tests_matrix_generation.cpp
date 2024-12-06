#include <cmath>
#include <gtest/gtest.h>
#include "../src/MatrixGeneratorFromFunction.hpp"
#include "../src/MatrixGeneratorFromFile.hpp"
#include "../src/FunctionManager.hpp"
#include "../src/FileReader.hpp"
#include "../src/FileReaderTXT.hpp"
#include "../src/FileReaderCSV.hpp"
#include "../src/FileReaderMTX.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <fstream>
#include <iostream>

using type_test = float; // choose float or double: enable to avoid redundent testing

// GENETATE MATRICES FROM FUNCTIONS

TEST(matrix_generator_from_function, generate_identity_matrix)
{
    // Arguments
    int nb_rows = 2;
    int nb_cols = 2;
    const std::string function_name = "identity";
    auto function = std::make_unique<FunctionManager<type_test>>(function_name);

    // Create the generator and generate the matrix
    MatrixGeneratorFromFunction<type_test> generator(std::move(function), nb_rows, nb_cols);
    auto matrix = generator.generate_matrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(2, 2);
    expected << 1.0, 0.0, 0.0, 1.0;

    ASSERT_TRUE(matrix != nullptr);
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected));                                                               // Compare matrices
    EXPECT_TRUE((std::is_same_v<typename std::remove_reference_t<decltype(*matrix)>::Scalar, type_test>)); // check type
}

TEST(matrix_generator_from_function, generate_hilbert_matrix)
{
    // Arguments
    int nb_rows = 3;
    int nb_cols = 3;
    const std::string function_name = "hilbert";
    auto function = std::make_unique<FunctionManager<type_test>>(function_name);

    // Create the generator and generate the matrix
    MatrixGeneratorFromFunction<type_test> generator(std::move(function), nb_rows, nb_cols);
    auto matrix = generator.generate_matrix();

    // Define the expected Hilbert matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << 1.0, 1.0 / 2.0, 1.0 / 3.0,
        1.0 / 2.0, 1.0 / 3.0, 1.0 / 4.0,
        1.0 / 3.0, 1.0 / 4.0, 1.0 / 5.0;

    ASSERT_TRUE(matrix != nullptr);
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-5));                                                         // Compare matrices with a tolerance
    EXPECT_TRUE((std::is_same_v<typename std::remove_reference_t<decltype(*matrix)>::Scalar, type_test>)); // check type
}

// GENETATE MATRICES FROM TXT FILES

TEST(matrix_generator_from_file, txt_file)
{
    const std::string file_name = "A.txt";
    auto file_reader = std::make_unique<FileReaderTXT<type_test>>(file_name);

    // Create the generator and generate the matrix
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));
    auto matrix = generator.generate_matrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0;

    ASSERT_TRUE(matrix != nullptr); // Ensure matrix is not null
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-5));                                                         // Compare matrices with a tolerance
    EXPECT_TRUE((std::is_same_v<typename std::remove_reference_t<decltype(*matrix)>::Scalar, type_test>)); // check type
}

TEST(matrix_generator_from_file, txt_empty)
{
    // Create a temporary empty file
    const std::string empty_file = "empty.txt";
    std::ofstream temp_file("../input/matrices/" + empty_file);
    temp_file.close();

    auto file_reader = std::make_unique<FileReaderTXT<type_test>>(empty_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove(("../input/matrices/" + empty_file).c_str());
}

TEST(matrix_generator_from_file, txt_invalid)
{
    const std::string invalid_file = "invalid_file.txt";
    std::ofstream temp_file("../input/matrices/" + invalid_file);
    temp_file << "1.0 2.0 3.0\n"
                 "4.0 5.0 invalid\n" // invalid entry
                 "7.0 8.0 9.0\n";
    temp_file.close();

    auto file_reader = std::make_unique<FileReaderTXT<type_test>>(invalid_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove(("../input/matrices/" + invalid_file).c_str());
}

TEST(matrix_generator_from_file, txt_inconsistent_columns)
{
    const std::string invalid_file = "inconsistent_columns.txt";
    std::ofstream temp_file("../input/matrices/" + invalid_file);
    temp_file << "1.0 2.0 3.0\n"
                 "4.0 5.0\n" // less columns: inconsistent
                 "7.0 8.0 9.0\n";
    temp_file.close();

    auto file_reader = std::make_unique<FileReaderTXT<type_test>>(invalid_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove(("../input/matrices/" + invalid_file).c_str());
}

TEST(matrix_generator_from_file, txt_no_file)
{
    const std::string invalid_file = "invalid_file.txt";

    auto file_reader = std::make_unique<FileReaderTXT<type_test>>(invalid_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove("../input/matrices/invalid_file.txt");
}

// GENETATE MATRICES FROM CSV FILES

TEST(matrix_generator_from_file, csv_file)
{
    const std::string file_name = "A.csv";
    auto file_reader = std::make_unique<FileReaderCSV<type_test>>(file_name);

    // Create the generator and generate the matrix
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));
    auto matrix = generator.generate_matrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0;

    ASSERT_TRUE(matrix != nullptr); // Ensure matrix is not null
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-5));                                                         // Compare matrices with a tolerance
    EXPECT_TRUE((std::is_same_v<typename std::remove_reference_t<decltype(*matrix)>::Scalar, type_test>)); // check type
}

TEST(matrix_generator_from_file, csv_empty)
{
    // Create a temporary empty file
    const std::string empty_file = "empty.csv";
    std::ofstream temp_file("../input/matrices/" + empty_file);
    temp_file.close();

    auto file_reader = std::make_unique<FileReaderCSV<type_test>>(empty_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove(("../input/matrices/" + empty_file).c_str());
}

TEST(matrix_generator_from_file, csv_invalid)
{
    const std::string invalid_file = "invalid_file.csv";
    std::ofstream temp_file("../input/matrices/" + invalid_file);
    temp_file << "1.0, 2.0, 3.0\n"
                 "4.0, 5.0, invalid\n" // invalid entry
                 "7.0, 8.0, 9.0\n";
    temp_file.close();

    auto file_reader = std::make_unique<FileReaderCSV<type_test>>(invalid_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove(("../input/matrices/" + invalid_file).c_str());
}

TEST(matrix_generator_from_file, csv_inconsistent_columns)
{
    const std::string invalid_file = "inconsistent_columns.csv";
    std::ofstream temp_file("../input/matrices/" + invalid_file);
    temp_file << "1.0, 2.0, 3.0\n"
                 "4.0, 5.0\n" // less columns: inconsistent
                 "7.0, 8.0, 9.0\n";
    temp_file.close();

    auto file_reader = std::make_unique<FileReaderTXT<type_test>>(invalid_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove(("../input/matrices/" + invalid_file).c_str());
}

TEST(matrix_generator_from_file, csv_no_file)
{
    const std::string invalid_file = "invalid_file.csv";

    auto file_reader = std::make_unique<FileReaderCSV<type_test>>(invalid_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove("../input/matrices/invalid_file.csv");
}

// GENETATE MATRICES FROM MTX FILES

TEST(matrix_generator_from_file, mtx_file)
{
    const std::string file_name = "B.mtx";
    auto file_reader = std::make_unique<FileReaderMTX<type_test>>(file_name);

    // Create the generator and generate the matrix
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));
    auto matrix = generator.generate_matrix();

    // Define the expected matrix
    Eigen::Matrix<type_test, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << 1.5, 0.0, 0.0,
        0.0, 2.5, 0.0,
        0.0, 0.0, 3.5;

    ASSERT_TRUE(matrix != nullptr); // Ensure matrix is not null
    EXPECT_EQ(matrix->rows(), expected.rows());
    EXPECT_EQ(matrix->cols(), expected.cols());
    EXPECT_TRUE(matrix->isApprox(expected, 1e-5));                                                         // Compare matrices with a tolerance
    EXPECT_TRUE((std::is_same_v<typename std::remove_reference_t<decltype(*matrix)>::Scalar, type_test>)); // check type
}

TEST(matrix_generator_from_file, mtx_empty)
{
    // Create a temporary empty file
    const std::string empty_file = "empty.mtx";
    std::ofstream temp_file("../input/matrices/" + empty_file);
    temp_file.close();

    auto file_reader = std::make_unique<FileReaderMTX<type_test>>(empty_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove(("../input/matrices/" + empty_file).c_str());
}

TEST(matrix_generator_from_file, mtx_invalid)
{
    const std::string invalid_file = "invalid_file.mtx";
    std::ofstream temp_file("../input/matrices/" + invalid_file);
    temp_file << "% this is a comment\n"
                 "% this is a second line of comments\n"
                 "3 3 6\n"
                 "1 1 invalid_entry"; // invalid_entry
    temp_file.close();

    auto file_reader = std::make_unique<FileReaderMTX<type_test>>(invalid_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove(("../input/matrices/" + invalid_file).c_str());
}

TEST(matrix_generator_from_file, mtx_no_file)
{
    const std::string invalid_file = "invalid_file.mtx";

    auto file_reader = std::make_unique<FileReaderMTX<type_test>>(invalid_file);
    MatrixGeneratorFromFile<type_test> generator(std::move(file_reader));

    EXPECT_THROW(generator.generate_matrix(), std::runtime_error);

    // Clean up the temporary file
    std::remove("../input/matrices/invalid_file.mtx");
}