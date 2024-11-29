
#ifndef __FILE_READER__HH__
#define __FILE_READER__HH__

#include <Eigen/Dense>
#include "constants.hpp"

template <typename T>
class FileReader
{
public:
    FileReader(const std::string &file_name) : file_name(file_name) {};
    virtual ~FileReader() {};
    virtual MatrixPointer<T> read_file() = 0;

protected:
    std::string file_name;
};

#endif