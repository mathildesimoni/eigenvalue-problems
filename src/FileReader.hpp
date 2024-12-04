
#ifndef __FILE_READER__HH__
#define __FILE_READER__HH__

#include <Eigen/Dense>
#include "constants.hpp"

/**
 * \brief A base class for reading matrices from files.
 *
 * This class serves as the base class for different file readers. It defines the
 * general interface for reading matrix data from files, but does not implement
 * the actual file reading logic. Derived classes must implement the `read_file` method.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class FileReader
{
public:
    FileReader(const std::string &file_name) : file_name(file_name) {}; /**< Constructor */
    virtual ~FileReader() {};                                           /**< Destructor */
    /**
     * \brief Pure virtual function to read a matrix from a file.
     *
     * This method must be overridden in derived classes to implement
     * the logic of reading the matrix data from a certain file.
     *
     * \return A pointer to an Eigen matrix containing the data read from the file.
     */
    virtual MatrixPointer<T> read_file() = 0;

protected:
    std::string file_name; /**< The name of the file to be read. */
};

#endif