#include "loaders/objloader.hpp"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include <objects/renderobject.hpp>
using namespace Objects;


RenderObject::RenderObject(){

}
RenderObject::RenderObject(const char * path, int texture, int shader){
    std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

    Loaders::Models::loadOBJ(path, Mesh.p_Vertices, Mesh.p_UVs, Mesh.p_Normals);
    TextureID = texture;
    ShaderID = shader;
    Transform.Scale = glm::vec3(1);
    Transform.Position = glm::vec3(0);
    ApplyTransform();
}

RenderObject::~RenderObject(){
    
}
void RenderObject::ApplyTransform(){

    double frameStartTime = glfwGetTime();
        
    Mesh.Vertices.clear();
    for(int i = 0; i < Mesh.p_Vertices.size(); i++){
        //initial
        Mesh.Vertices.push_back(Mesh.p_Vertices[i]);
        //rotation
        //TODO:rotation

        //scale
        Mesh.Vertices[i].x *= Transform.Scale.x;
        Mesh.Vertices[i].y *= Transform.Scale.y;
        Mesh.Vertices[i].z *= Transform.Scale.z;

        //position
        if(Transform.Position != Transform.cache_Position)
        {Mesh.Vertices[i].x += Transform.Position.x;
        Mesh.Vertices[i].y += Transform.Position.y;
        Mesh.Vertices[i].z += Transform.Position.z;}
    }
    Mesh.Normals.clear();
    for(int i = 0; i < Mesh.p_Normals.size(); i++){
        //initial
        Mesh.Normals.push_back(Mesh.p_Normals[i]);
        //rotation
        //TODO:rotation
        
        //scale
        Mesh.Normals[i].x *= Transform.Scale.x;
        Mesh.Normals[i].y *= Transform.Scale.y;
        Mesh.Normals[i].z *= Transform.Scale.z;

        //position
        if(Transform.Position != Transform.cache_Position)
        {Mesh.Normals[i].x += Transform.Position.x;
        Mesh.Normals[i].y += Transform.Position.y;
        Mesh.Normals[i].z += Transform.Position.z;}
    }
    Mesh.UVs.clear();
    for(int i = 0; i < Mesh.p_UVs.size(); i++){
        Mesh.UVs.push_back(Mesh.p_UVs[i]);
    }
    Transform.cache_Position = Transform.Position;
    Transform.Rotation = Transform.Rotation;
    Transform.Scale = Transform.Scale;
}

void transform::Update(){
    PendingUpdate = true;
}
void transform::Update(transform _new){
    Position = _new.Position;
    Rotation = _new.Rotation;
    Scale = _new.Scale;
    PendingUpdate = true;
}
void transform::UpdatePos(glm::vec3 _new){
    Position = _new;
    PendingUpdate = true;
}