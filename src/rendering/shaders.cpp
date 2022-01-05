#define GLEW_STATIC
#include <GL/glew.h>
#include <rendering/shaders.hpp>
#include <rendering/render.hpp>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>


static const GLchar* vertex_shader_source =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
    "layout(location = 1) in vec3 vertexColor;\n"
    "out vec3 fragmentColor;\n"
    "uniform mat4 MVP;\n"
    "void main() {\n"
    "    gl_Position.xyz = vertexPosition_modelspace;\n"
    "    gl_Position.w = 1.0;\n"
    "    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);\n"
    "    fragmentColor = vertexColor;\n"
    "}\n";
static const GLchar* fragment_shader_source =
    "#version 330 core\n"
    "in vec3 fragmentColor;\n"
    "out vec3 color;\n"
    "void main() {\n"
    "    color = fragmentColor;\n"
    "}\n";


GLuint fragment_shader, vertex_shader;


GLuint Shaders::GetShaders() {
    GLint log_length, success;
    GLuint  program;

    /* Vertex shader */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {

    }
    if (!success) {
        printf("vertex shader compile error\n");
        exit(EXIT_FAILURE);
    }

    /* Fragment shader */
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
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

    /* Link shaders */
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        std::cout << "uh, fucK?" << std::endl;
    }
    if (!success) {
        printf("shader link error");
        exit(EXIT_FAILURE);
    }

    /* Cleanup. */
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}