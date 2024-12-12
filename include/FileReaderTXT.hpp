
#ifndef __FILE_READER_TXT__HH__
#define __FILE_READER_TXT__HH__

#include "FileReader.hpp"

/**
 * \brief Class for reading matrices from TXT files.
 *
 * This class extends the FileReader base class to provide functionality
 * for reading TXT files and storing them in Eigen matrices.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class FileReaderTXT : public FileReader<T>
{
public:
    FileReaderTXT(const std::string &fileName); /**< Constructor */
    ~FileReaderTXT();                           /**< Destructor */
    /**
     * \brief Reads the matrix data from the TXT file line-by-line and store it in an Eigen matrix object.
     * \return A pointer to an Eigen matrix containing the data read from the TXT file.
     */
    MatrixPointer<T> ReadFile() override;
};

#endif