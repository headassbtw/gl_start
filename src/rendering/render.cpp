
#include "objects/renderobject.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/common.hpp>
#include <glm/fwd.hpp>
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

GLuint SwapShader;

int obj;
GLuint MatrixID;
GLuint TextureID;
GLuint ViewMatrixID;
GLuint ModelMatrixID;
GLuint LightID;

std::vector<Objects::RenderObject*> objects;
std::vector<GLuint> shaders;
std::vector<GLuint> textures;


std::vector< glm::vec3 > vert_render;
std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec2 > uv_render;
std::vector< glm::vec3 > normals;
std::vector< glm::vec3 > normal_render;

int skyboxverts = 0;

glm::vec3 pos;
glm::vec3 look;
double horizontalAngle, verticalAngle;
auto vertical_limit = glm::radians(89.9f);
auto vertical_base = glm::radians(-89.9f);
float sens = 0.7f;


void HandleProjection(){
    glm::mat4 Projection = glm::perspective(glm::radians(90.0f), (float) WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 150.0f);
    glm::mat4 View = glm::lookAt(
    glm::vec3(pos.x,pos.y,pos.z),                               //position
    glm::vec3(look.x + pos.x,look.y + pos.y,look.z + pos.z),    //point at a point
    glm::vec3(0,1,0)
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
void HandleTransforms(){
    for(int i = 0; i < objects.size(); i++){
        if(i == 0){                                 // the skybox
            for(int j = 0; j < objects[0]->Mesh.Vertices.size(); j++){
                vert_render[j] = 
                glm::vec3(
                objects[i]->Mesh.Vertices[j].x + pos.x,
                objects[i]->Mesh.Vertices[j].y + pos.y,
                objects[i]->Mesh.Vertices[j].z + pos.z
                )
                ;
            }
        }
        else if(objects[i]->Transform.PendingUpdate) // every other object
        {
            
            
            objects[i]->ApplyTransform();
            objects[i]->Transform.PendingUpdate = false;

            int v_idx = objects[i]->Mesh.vert_buffer_idx;
            int u_idx = objects[i]->Mesh.uv_buffer_idx;
            int n_idx = objects[i]->Mesh.normal_buffer_idx;

            

            for(int j = v_idx; j < v_idx + objects[i]->Mesh.Vertices.size(); j++){
                vert_render[j] = (objects[i]->Mesh.Vertices[j - v_idx]);
            }
            for(int j = u_idx; j < u_idx + objects[i]->Mesh.UVs.size(); j++){
                uv_render[j] = (objects[i]->Mesh.UVs[j - u_idx]);
            }
            for(int j = n_idx; j < n_idx + objects[i]->Mesh.Normals.size(); j++){
                normal_render[j] = (objects[i]->Mesh.Normals[j - n_idx]);
            }
        }

    }
    double frameEndTime = glfwGetTime();
}




float speed = 1.0f;
float strafe_mod = 0.75f;
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


    if (glfwGetKey( Window, GLFW_KEY_D ) == GLFW_PRESS){

        glm::vec3 lookr;
        lookr.x = cos(verticalAngle) * sin(horizontalAngle - 90);
        lookr.z = cos(verticalAngle) * cos(horizontalAngle - 90);

        pos += lookr * speed * strafe_mod* Time::DeltaTime;
    }
    if (glfwGetKey( Window, GLFW_KEY_A ) == GLFW_PRESS){

        glm::vec3 lookl;
        lookl.x = cos(verticalAngle) * sin(horizontalAngle + 90);
        lookl.z = cos(verticalAngle) * cos(horizontalAngle + 90);

        pos += lookl * speed * strafe_mod* Time::DeltaTime;
    }
    

    if (glfwGetKey( Window, GLFW_KEY_W ) == GLFW_PRESS){
        pos += look * speed * Time::DeltaTime;
    }
    if (glfwGetKey( Window, GLFW_KEY_S ) == GLFW_PRESS){
        pos -= look * speed * Time::DeltaTime;
    }
    if (glfwGetKey( Window, GLFW_KEY_Z ) == GLFW_PRESS){
        double zs = glfwGetTime();
        auto shit = Objects::transform();
        shit.Position = glm::vec3(0,objects[1]->Transform.Position.y + 0.05f,0);
        shit.Rotation = glm::vec3(0,0,0);
        shit.Scale = glm::vec3(1,1,1);
        objects[1]->Transform.Update(shit);
        double ze = glfwGetTime();
        //printf("holding Z cost you %fms\n",(ze-zs)*1000);
    }
    HandleTransforms();
    HandleProjection();
        
}
void SwitchShader(int program){
    GLuint prog = shaders[program];
    glUseProgram(prog);
    MatrixID = glGetUniformLocation(prog, "MVP");
    ViewMatrixID = glGetUniformLocation(prog, "V");
	ModelMatrixID = glGetUniformLocation(prog, "M");
    SwapShader = glGetUniformLocation(prog, "Lit");
    
    TextureID  = glGetUniformLocation(prog, "textureSampler");
    LightID = glGetUniformLocation(prog, "LightPosition_worldspace");
}

float skybox_scale = 100.0f;
void Render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    glActiveTexture(GL_TEXTURE0);

    if (glfwGetKey( Window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
        speed = 1.5f;
    }
    else{
        speed = 1.0f;
    }

    double frameStartTime = glfwGetTime();
    
    
    model_render::Bind_Buffers(vert_render, uv_render,normal_render);
    model_render::Prepare_Buffers();
    int vert_idx = 0;
    for(int i = 0; i < objects.size(); i++){
        int shdr = objects[i]->ShaderID;
        int tex = objects[i]->TextureID;


        
        
        
        SwitchShader(shdr);
        HandleProjection();
        glUniform1i(TextureID, tex);
        glBindTexture(GL_TEXTURE_2D, textures[tex]);
        glDrawArrays(GL_TRIANGLES, vert_idx, vert_idx + objects[i]->Mesh.Vertices.size());
        vert_idx += objects[i]->Mesh.Vertices.size();
    }


    model_render::Cleanup_Buffers();


    glfwSwapBuffers(Window);
}




int Run(){
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

    objects.push_back(new Objects::RenderObject("content/models/skybox.obj",0,1));
    objects[0]->Transform.Scale = glm::vec3(30);
    objects[0]->ApplyTransform();
    objects.push_back(new Objects::RenderObject("content/models/cube.obj",1,0));
    objects[1]->ApplyTransform();
    objects.push_back(new Objects::RenderObject("content/models/spher.obj",2,0));
    objects[2]->Transform.Position = glm::vec3(0,16,0);
    objects[2]->ApplyTransform();
    printf("%z  u meshes loaded\n", objects.size());
    
    model_render::Bind_Buffers(vert_render, uv_render,normal_render);
    
    
    
    
    shaders.clear();
    shaders.push_back(Shaders::GetShaders("shaders/vert.glsl","shaders/frag_lit.glsl"));
    shaders.push_back(Shaders::GetShaders("shaders/vert.glsl","shaders/frag_unlit.glsl"));
    shaders.push_back(Shaders::GetShaders("shaders/vert.glsl","shaders/frag_lit.glsl"));
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.1f, 0.3f, 0.5f);
    textures.clear();
    textures.push_back(Loaders::Textures::LoadDDS("content/textures/skybox.dds"));
    textures.push_back(Loaders::Textures::LoadDDS("content/textures/coob.dds"));
    textures.push_back(Loaders::Textures::LoadDDS("content/textures/spher.dds"));
    



    for(int i = 0; i < objects.size(); i++){
        objects[i]->Mesh.vert_buffer_idx = vert_render.size();
        objects[i]->Mesh.uv_buffer_idx = uv_render.size();
        objects[i]->Mesh.normal_buffer_idx = normal_render.size();
        for(int j = 0; j < objects[i]->Mesh.Vertices.size(); j++){
            vert_render.push_back(objects[i]->Mesh.Vertices[j]);
        }
        for(int j = 0; j < objects[i]->Mesh.UVs.size(); j++){
            uv_render.push_back(objects[i]->Mesh.UVs[j]);
        }
        for(int j = 0; j < objects[i]->Mesh.Normals.size(); j++){
            normal_render.push_back(objects[i]->Mesh.Normals[j]);
        }
        objects[i]->Transform.PendingUpdate = true;
    }
    do{
        double frameStartTime = glfwGetTime();
        glfwPollEvents();
        Update();
        Render();
        double frameEndTime = glfwGetTime();
        Time::DeltaTime = float(frameEndTime - frameStartTime);
    }
    while(glfwGetKey(Window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
    glfwWindowShouldClose(Window) == 0);



    return 0;
}