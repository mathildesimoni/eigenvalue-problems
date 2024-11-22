
#ifndef __FILE_READER_CSV__HH__
#define __FILE_READER_CSV__HH__

#include <Eigen/Dense>
#include "FileReader.hpp"

template <typename T>
class FileReaderCSV : public FileReader<T>
{
public:
    FileReaderCSV(const std::string &file_name);
    ~FileReaderCSV();
    std::unique_ptr<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> read_file() override;
};

#endif