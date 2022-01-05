#define GLEW_STATIC
#include <GL/glew.h>
#include <rendering/shaders.hpp>
#include <loaders/textloader.hpp>
#include <rendering/render.hpp>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <content/filesystem.hpp>
using namespace Content::Filesystem;
GLuint master_fragment, fragment_shader, fragment_shader_2, vertex_shader;


GLuint Shaders::GetShaders(int shaderset) {
    GLint log_length, success;
    GLuint  program;
    
    std::string VertSource = GetText("shaders/vert.glsl");
    std::string MasterFrag = GetText("shaders/masterfrag.glsl");
    std::string FragSource = GetText("shaders/frag.glsl");
    std::string Frag2Source = GetText("shaders/frag2.glsl");
    const char* VertexSourcePointer = VertSource.c_str();
    const char* MasterFragmentPointer = MasterFrag.c_str();
    const char* FragmentSourcePointer = FragSource.c_str();
    const char* Fragment2SourcePointer = Frag2Source.c_str();
    /* Vertex shader */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &VertexSourcePointer, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
    if ( log_length > 0 ){
		std::vector<char> VertexShaderErrorMessage(log_length+1);
		glGetShaderInfoLog(vertex_shader, log_length, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
    if (!success) {
        printf("vertex shader compile error\n");
        exit(EXIT_FAILURE);
    }



    /* Fragment shader */
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &FragmentSourcePointer, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        std::cout << "frag shader died?" << std::endl;
    }
    if (!success) {
        printf("fragment shader compile error\n");
        exit(EXIT_FAILURE);
    }

    fragment_shader_2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_2, 1, &Fragment2SourcePointer, NULL);
    glCompileShader(fragment_shader_2);
    glGetShaderiv(fragment_shader_2, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragment_shader_2, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        std::cout << "frag shader 2 died?" << std::endl;
    }
    if (!success) {
        printf("fragment shader 2 compile error\n");
        exit(EXIT_FAILURE);
    }

    /* Fragment shader */
    master_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(master_fragment, 1, &MasterFragmentPointer, NULL);
    glCompileShader(master_fragment);
    glGetShaderiv(master_fragment, GL_COMPILE_STATUS, &success);
    glGetShaderiv(master_fragment, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        std::vector<char> MasterFragError(log_length+1);
		glGetShaderInfoLog(master_fragment, log_length, NULL, &MasterFragError[0]);
		printf("%s\n", &MasterFragError[0]);
    }
    if (!success) {
        printf("master fragment shader compile error\n");
        exit(EXIT_FAILURE);
    }



    /* Link shaders */
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
        glAttachShader(program, master_fragment);
        glAttachShader(program, fragment_shader);
        glAttachShader(program, fragment_shader_2);
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        std::vector<char> ShaderLinkError(log_length+1);
		glGetShaderInfoLog(program, log_length, NULL, &ShaderLinkError[0]);
		printf("%s\n", &ShaderLinkError[0]);
        std::cout << "uh, fucK?" << std::endl;
    }
    if (!success) {
        printf("shader link error");
        exit(EXIT_FAILURE);
    }

    /* Cleanup. */
    glDeleteShader(vertex_shader);
        glDeleteShader(master_fragment);
        glDeleteShader(fragment_shader);
        glDeleteShader(fragment_shader_2);
    return program;
}