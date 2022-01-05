#include "loaders/textloader.hpp"
#include <content/filesystem.hpp>
#include <cstdio>
#include <cstring>
#include <streambuf>
#include <string>
#include <defs.hpp>
bool Virtual = false;
const char* path = "content";
void Content::Filesystem::Initialize(bool virt){
    Initialize(virt,"content");
}
void Content::Filesystem::Initialize(bool virt, const char* contentfolderpath){
    Virtual = virt;
    path = contentfolderpath;
}
std::string fullContentPath(const char* filepath){
    int bufsize = strlen(filepath) + strlen(path) + sizeof(FILEPATH_DELIMITER);
        char buffer[bufsize];
        strncpy(buffer, path, sizeof(buffer));
        strncat(buffer, FILEPATH_DELIMITER, bufsize);
        strncat(buffer, filepath, bufsize);
        return std::string(buffer);
}



std::string Content::Filesystem::GetText(const char* filepath){
    if(Virtual){
        //virtual file shit
    }
    else{
        
        std::string path = fullContentPath(filepath);
        printf("[Filesystem] Loading:%s\n", path.c_str());
        std::string r = Loaders::Text::LoadFile(path.c_str());
        return r;
    }

}