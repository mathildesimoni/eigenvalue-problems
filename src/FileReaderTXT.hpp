
#ifndef __FILE_READER_TXT__HH__
#define __FILE_READER_TXT__HH__

#include <Eigen/Dense>
#include "FileReader.hpp"

template <typename T>
class FileReaderTXT : public FileReader<T>
{
public:
    FileReaderTXT(const std::string &file_name);
    ~FileReaderTXT();
    std::unique_ptr<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> read_file() override;
};

#endif