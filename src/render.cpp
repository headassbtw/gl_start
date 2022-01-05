#include <cstdio>
#include <render.hpp>
#include <GL/glew.h>

#include <GLFW/glfw3.h>

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

    GLFWwindow* Window;
    Window = glfwCreateWindow(1600, 900, "OpenGL", NULL, NULL);
    if(Window = NULL){
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

    do{
        glClear(GL_COLOR_BUFFER_BIT);

        //render shit!


        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    while(glfwGetKey(Window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
    glfwWindowShouldClose(Window) == 0);



    return 0;
}