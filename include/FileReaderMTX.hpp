
#ifndef __FILE_READER_MTX__HH__
#define __FILE_READER_MTX__HH__

#include "FileReader.hpp"

/**
 * \brief Class for reading matrices from MTX files.
 *
 * This class extends the FileReader base class to provide functionality
 * for reading MTX files and storing them in Eigen matrices.
 *
 * \tparam T The data type of the matrix elements (e.g. float, double).
 */
template <typename T>
class FileReaderMTX : public FileReader<T>
{
public:
    /// Constructor
    FileReaderMTX(const std::string &fileName);
    /// Destructor
    ~FileReaderMTX();
    /**
     * \brief Reads the matrix data from the MTX file line-by-line and store it in an Eigen matrix object.
     * \return A pointer to an Eigen matrix containing the data read from the MTX file.
     */
    MatrixPointer<T> ReadFile() override;
};

#endif