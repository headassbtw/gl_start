#include <rendering/objectrender.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

GLuint vertexbuffer;
GLuint colorbuffer;
GLuint VertexArrayID;

static const GLfloat g_vertex_buffer_data[] = {
   -0.5f, -0.5f, 0.0f,      //1
   0.5f, -0.5f, 0.0f,       //1
   -0.5f,  0.5f, 0.0f,      //1
   0.5f, 0.5f, 0.0f,        //2
   0.5f, -0.5f, 0.0f,       //2
   -0.5f,  0.5f, 0.0f,      //2
    };
static const GLfloat g_color_buffer_data[] = {
   1.0f,  0.0f, 0.0f,      //1
   1.0f,  0.0f, 0.0f,      //1
   1.0f,  0.0f, 0.0f,      //1
   0.0f,  0.0f, 1.0f,      //2
   0.0f,  0.0f, 1.0f,      //2
   0.0f,  0.0f, 1.0f,      //2
    };


void obj_render::Bind_Buffer(){
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}

void obj_render::Show_Cube(){
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
    1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
    3,                                // size
    GL_FLOAT,                         // type
    GL_FALSE,                         // normalized?
    0,                                // stride
    (void*)0                          // array buffer offset
    );


    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 2*3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}