
#ifndef __FILE_READER_MTX__HH__
#define __FILE_READER_MTX__HH__

#include <Eigen/Dense>
#include "FileReader.hpp"

template <typename T>
class FileReaderMTX : public FileReader<T>
{
public:
    FileReaderMTX(const std::string &file_name);
    ~FileReaderMTX();
    MatrixPointer<T> read_file() override;
};

#endif