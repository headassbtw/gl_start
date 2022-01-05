#include <GL/glew.h>
#include <GL/gl.h>
#include <rendering/shaders.hpp>
#include <cstdio>
#include <rendering/render.hpp>

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <rendering/objectrender.hpp>

GLFWwindow* Window;

int Render(){
    glewExperimental = true;
    if(!glfwInit()){
        fprintf(stderr, "Could not initialize GLFW\n");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    Window = glfwCreateWindow(1600, 900, "OpenGL", NULL, NULL);
    if(Window == NULL){
        fprintf(stderr, "Failed to open window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Window);
    glewExperimental = true;
    if(glewInit() != GLEW_OK){
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    //now the real stuff begins!
    glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);
    obj_render::Bind_Buffer();
    GLuint progID = Shaders::GetShaders();
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(progID);
    glClearColor(0.0f, 0.1f, 0.3f, 0.5f);


    glm::mat4 Projection = glm::perspective(glm::radians(90.0f), (float) 1600 / (float)900, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
    glm::vec3(0,0,0), // and looks at the origin
    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model;
    GLuint MatrixID = glGetUniformLocation(progID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);








    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        




        //render shit!
        obj_render::Show_Cube();

        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    while(glfwGetKey(Window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
    glfwWindowShouldClose(Window) == 0);



    return 0;
}