#include <content/binaryio.hpp>
#include <fstream>
int BinaryIO::ReadInt(std::ifstream *stream){
    int a;
	stream->read(reinterpret_cast<char *>(&a), sizeof(a));
    return a;
}
float BinaryIO::ReadFloat(std::ifstream *stream){
    float a;
	stream->read(reinterpret_cast<char *>(&a), sizeof(a));
    return a;
}