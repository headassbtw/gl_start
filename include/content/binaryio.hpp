#pragma once
#include <fstream>
namespace BinaryIO{
    int ReadInt(std::ifstream *stream);
    float ReadFloat(std::ifstream *stream);
}