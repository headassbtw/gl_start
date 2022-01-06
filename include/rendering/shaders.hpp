#pragma once
#include <GL/gl.h>
namespace Shaders{
    GLuint CreateFrag(const char* path);
    GLuint CreateVert(const char* path);
    GLuint GetShaders(const char* vert, const char* frag);

}