#include <loaders/textloader.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string Loaders::Text::LoadFile(const char* path){
    std::string FileContents;
	std::ifstream TextFileStream(path, std::ios::in);
	if(TextFileStream.is_open()){
		std::stringstream sstr;
		sstr << TextFileStream.rdbuf();
		FileContents = sstr.str();
		TextFileStream.close();
	}else{
		fprintf(stderr,"Could not load %s.\n", path);
		getchar();
		return 0;
	}
    return FileContents;
}