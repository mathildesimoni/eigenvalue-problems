
#ifndef __FILE_READER_CSV__HH__
#define __FILE_READER_CSV__HH__

#include "FileReader.hpp"

/**
 * \brief Class for reading matrices from CSV files.
 *
 * This class extends the FileReader base class to provide functionality
 * for reading CSV files and storing them in Eigen matrices.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class FileReaderCSV : public FileReader<T>
{
public:
    FileReaderCSV(const std::string &fileName); /**< Constructor */
    ~FileReaderCSV();                           /**< Destructor */
    /**
     * \brief Reads the matrix data from the CSV file line-by-line and store it in an Eigen matrix object.
     *
     * \return A pointer to an Eigen matrix containing the data read from the CSV file.
     */
    MatrixPointer<T> ReadFile() override;
};

#endif