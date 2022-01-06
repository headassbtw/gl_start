#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <rendering/shaders.hpp>
#include <loaders/textloader.hpp>
#include <rendering/render.hpp>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdarg>
#include <content/filesystem.hpp>
using namespace Content::Filesystem;
GLuint master_fragment, fragment_shader, fragment_shader_2, vertex_shader;
GLint log_length, success;
GLuint Shaders::CreateFrag(const char *path){
    GLuint rtnShader;
    std::string ShaderSource = GetText(path);
    const char* ShaderSourcePointer = ShaderSource.c_str();

    rtnShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(rtnShader, 1, &ShaderSourcePointer, NULL);
    glCompileShader(rtnShader);
    glGetShaderiv(rtnShader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(rtnShader, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        printf("fragment shader compile error:\n");
        std::vector<char> FragError(log_length+1);
		glGetShaderInfoLog(rtnShader, log_length, NULL, &FragError[0]);
		printf("%s\n", &FragError[0]);
    }
    if (!success) {
        exit(EXIT_FAILURE);
    }
    printf("Compiled fragment shader \"%s\"\n",path);
    return rtnShader;
}
GLuint Shaders::CreateVert(const char *path){
    GLuint rtnShader;
    std::string ShaderSource = GetText(path);
    const char* ShaderSourcePointer = ShaderSource.c_str();
    rtnShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(rtnShader, 1, &ShaderSourcePointer, NULL);
    glCompileShader(rtnShader);
    glGetShaderiv(rtnShader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(rtnShader, GL_INFO_LOG_LENGTH, &log_length);
    if ( log_length > 0 ){
        printf("vertex shader compile error:\n");
		std::vector<char> VertexShaderErrorMessage(log_length+1);
		glGetShaderInfoLog(rtnShader, log_length, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
    if (!success) {
        exit(EXIT_FAILURE);
    }
    printf("Compiled vertex shader \"%s\"\n",path);
    return rtnShader;
}



GLuint Shaders::GetShaders(const char* vert, const char* frag) {
    GLuint  program;
    
    vertex_shader = Shaders::CreateVert(vert);
    master_fragment = Shaders::CreateFrag(frag);
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, master_fragment);
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        printf("shader link error for program %d:\n", program);
        std::vector<char> ShaderLinkError(log_length);
		glGetShaderInfoLog(program, log_length, NULL, &ShaderLinkError[0]);
		printf("%s\n", &ShaderLinkError[0]);
        
    }
    if (!success) {
        exit(EXIT_FAILURE);
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(master_fragment);
    return program;
}