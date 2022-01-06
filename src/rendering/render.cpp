
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <rendering/shaders.hpp>
#include <cstdio>
#include <vector>
#include <rendering/render.hpp>
#include <time.hpp>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <rendering/modelrender.hpp>
#include <string>
#include <defs.hpp>
#include <loaders/textureloader.hpp>
#include <loaders/objloader.hpp>
GLFWwindow* Window;

GLuint progID;
GLuint progID2;
GLuint SwapShader;

GLuint MatrixID;
GLuint TextureID;
GLuint ViewMatrixID;
GLuint ModelMatrixID;
GLuint LightID;

GLuint Texture;
GLuint Texture2;

std::vector< glm::vec3 > og_vertices;
std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;

int skyboxverts = 0;

glm::vec3 pos;
glm::vec3 look;
double horizontalAngle, verticalAngle;
auto vertical_limit = glm::radians(89.9f);
auto vertical_base = glm::radians(-89.9f);
float sens = 0.7f;
<<<<<<< HEAD


void HandleProjection(){
    glm::mat4 Projection = glm::perspective(glm::radians(90.0f), (float) WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 150.0f);
    glm::mat4 View = glm::lookAt(
    glm::vec3(pos.x,pos.y,pos.z),                               //position
    glm::vec3(look.x + pos.x,look.y + pos.y,look.z + pos.z),    //point at a point
    glm::vec3(0,(glfwGetKey( Window, GLFW_KEY_A ) == GLFW_RELEASE) ? 1 : -1,0)
    );
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model;
    glm::mat4 ViewMatrix = mvp;
    glm::mat4 ModelMatrix = glm::mat4(1.0);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

    glm::vec3 lightPos = glm::vec3(4,4,-4);
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
}

=======
float speed = 1.0f;
>>>>>>> 98979a5fb9c70d24caa8e637a421cf89be40d0a1
void Update(){
    double xpos, ypos;
    glfwGetCursorPos(Window, &xpos, &ypos);
    if(glfwGetKey( Window, GLFW_KEY_GRAVE_ACCENT ) == GLFW_RELEASE){
        //when tilde is not held, temporary mouse lock disable key
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPos(Window, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    }
    else{
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    horizontalAngle += Time::DeltaTime * sens * float(WINDOW_WIDTH/2 - xpos );
    verticalAngle   += Time::DeltaTime * sens * float( WINDOW_HEIGHT/2 - ypos );
    if(glm::degrees(verticalAngle) > 89.9f ) verticalAngle = vertical_limit;
    if(glm::degrees(verticalAngle) < -89.9f ) verticalAngle = vertical_base;

    look.x = cos(verticalAngle) * sin(horizontalAngle);
    look.y =sin(verticalAngle);
    look.z = cos(verticalAngle) * cos(horizontalAngle);


    

    if (glfwGetKey( Window, GLFW_KEY_W ) == GLFW_PRESS){
        pos += look * speed * Time::DeltaTime;
    }
    if (glfwGetKey( Window, GLFW_KEY_S ) == GLFW_PRESS){
        pos -= look * speed * Time::DeltaTime;
    }
    HandleProjection();
        
}
void SwitchShader(GLuint prog){
    glUseProgram(prog);
    MatrixID = glGetUniformLocation(prog, "MVP");
    ViewMatrixID = glGetUniformLocation(prog, "V");
	ModelMatrixID = glGetUniformLocation(prog, "M");
    SwapShader = glGetUniformLocation(prog, "Lit");
    
    TextureID  = glGetUniformLocation(prog, "textureSampler");
    LightID = glGetUniformLocation(prog, "LightPosition_worldspace");
}

float skybox_scale = 100.0f;
void RenderUpdate(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    glActiveTexture(GL_TEXTURE0);

    if (glfwGetKey( Window, GLFW_KEY_SPACE ) == GLFW_PRESS){
        glUniform1f(SwapShader, 1);
        SwitchShader(progID2);
        glBindTexture(GL_TEXTURE_2D, Texture2);
    }
    else{
        glUniform1f(SwapShader, 0);
        SwitchShader(progID);
        glBindTexture(GL_TEXTURE_2D, Texture);
    }
<<<<<<< HEAD
=======

    if (glfwGetKey( Window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
        speed = 1.5f;
    }
    else{
        speed = 1.0f;
    }

    glUniform1i(TextureID, 0);
>>>>>>> 98979a5fb9c70d24caa8e637a421cf89be40d0a1

    int last = vertices.size()-1;
    for(int i = 0; i < skyboxverts; i++){
        vertices[i].x = (og_vertices[i].x * skybox_scale) + pos.x;
        vertices[i].y = (og_vertices[i].y * skybox_scale) + pos.y;
        vertices[i].z = (og_vertices[i].z * skybox_scale) + pos.z;
    }
    

    
    model_render::Bind_Buffers(vertices, uvs,normals);

    model_render::Prepare_Buffers();



    SwitchShader(progID2);
    glUniform1f(SwapShader, 0);
    glBindTexture(GL_TEXTURE_2D, Texture2);
    HandleProjection();
    glDrawArrays(GL_TRIANGLES, 0, skyboxverts);

    SwitchShader(progID);
    glUniform1f(SwapShader, 1);
    glBindTexture(GL_TEXTURE_2D, Texture);
    HandleProjection();
    glDrawArrays(GL_TRIANGLES, skyboxverts, vertices.size());


    model_render::Cleanup_Buffers();


    glfwSwapBuffers(Window);
}




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

    
    Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "i haven't found a practical limit to how long window titles can be, and at this point i'm sure there has to be one but i'm not sure what it would be, but to be fair i haven't seen any long titles", NULL, NULL);
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

    glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_FALSE);
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    std::vector< glm::vec3 > t_vertices;
std::vector< glm::vec2 > t_uvs;
std::vector< glm::vec3 > t_normals;

    //addAxisShit();
    bool res_skybox = Loaders::Models::loadOBJ("content/models/skybox.cob", og_vertices, uvs, normals);
    if(!res_skybox){
        fprintf(stderr, "FUCKED UP THE SKYBOX LMAO\n");
        return -1;
    }
    skyboxverts = og_vertices.size();
    bool shitass = Loaders::Models::loadCOB("content/models/shitass.cob", og_vertices, uvs, normals);
    bool res = Loaders::Models::loadOBJ("content/models/cube.cob", og_vertices, uvs, normals);
    printf("meshes loaded\n");
    
    model_render::Bind_Buffers(og_vertices, uvs,normals);
    
    for(int i = 0; i < og_vertices.size();i++){
        vertices.push_back(og_vertices[i]);
    }
    
    progID = Shaders::GetShaders("shaders/vert.glsl","shaders/masterfrag.glsl");
    progID2 = Shaders::GetShaders("shaders/vert.glsl","shaders/masterfrag.glsl");
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.1f, 0.3f, 0.5f);
    Texture = Loaders::Textures::LoadDDS("content/textures/coob.dds");
    Texture2 = Loaders::Textures::LoadDDS("content/textures/skybox.dds");
    SwitchShader(progID);
    do{
        double frameStartTime = glfwGetTime();
        glfwPollEvents();
        Update();
        RenderUpdate();
        double frameEndTime = glfwGetTime();
        Time::DeltaTime = float(frameEndTime - frameStartTime);
    }
    while(glfwGetKey(Window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
    glfwWindowShouldClose(Window) == 0);



    return 0;
}