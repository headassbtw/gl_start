#include "content/filesystem.hpp"
#include <cstring>
#include <iostream>
#include <rendering/render.hpp>
int main(int argc, char* argv[]){
    bool virt = false;
    for(int a = 0; a < argc; a++){
        if(strcmp(argv[a], "--virtual") == 0) virt = true;
    }
    Content::Filesystem::Initialize(virt);
    std::cout << "Hello World!" << std::endl;
    
    return Render();
}