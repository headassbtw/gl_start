#pragma once
#include <GL/gl.h>
namespace Loaders{
    namespace Textures{
        GLuint LoadBMP_Custom(const char* path);
        GLuint LoadDDS(const char* path);
    }
}