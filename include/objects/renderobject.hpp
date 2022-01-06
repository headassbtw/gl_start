#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <vector>
namespace Objects{
    struct RenderObject{
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> UVs;
        std::vector<glm::vec3> Normals;
        int TextureID;
        int ShaderID;
        RenderObject();
        RenderObject(const char * path);
        ~RenderObject();
    };
    
}