
#ifndef __FILE_READER__HH__
#define __FILE_READER__HH__

#include "constants.hpp"

/**
 * \brief Abstract base class for reading matrices from files.
 *
 * This class serves as the base class for different file readers. It defines the
 * general interface for reading matrix data from files, but does not implement
 * the actual file reading logic. Derived classes must implement the `ReadFile()` method.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class FileReader
{
public:
    /// Constructor
    FileReader(const std::string &fileName) : fileName(fileName) {};
    /// Destructor
    virtual ~FileReader() {};
    /**
     * \brief Pure virtual function to read a matrix from a file.
     *
     * This method must be overridden in derived classes to implement
     * the logic of reading the matrix data from a certain file.
     *
     * \return A pointer to an Eigen matrix containing the data read from the file.
     */
    virtual MatrixPointer<T> ReadFile() = 0;

protected:
    std::string fileName; /**< The name of the file to be read. */
};

/**
 * \brief Class to handle file-related errors.
 *
 * This class is derived from `std::exception` and is used to represent
 * errors specifically related to file operations.
 */
class FileException : public std::exception
{
    std::string message; /**< Custom error message */

public:
    FileException(const std::string &msg) : message(msg) {} /**< Constructor */
    /// Retrieve the error message
    const char *what() const throw()
    {
        return message.c_str();
    }
};

#endif