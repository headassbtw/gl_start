#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <vector>
namespace Objects{
    struct mesh{
        std::vector<glm::vec3> p_Vertices;
        std::vector<glm::vec2> p_UVs;
        std::vector<glm::vec3> p_Normals;
        std::vector<glm::vec3> Vertices;
        std::vector<glm::vec2> UVs;
        std::vector<glm::vec3> Normals;
        int vert_buffer_idx;
        int uv_buffer_idx;
        int normal_buffer_idx;
    };
    struct transform{
        glm::vec3 Position;
        glm::vec3 Rotation;
        glm::vec3 Scale;
        glm::vec3 cache_Position;
        glm::vec3 cache_Rotation;
        glm::vec3 cache_Scale;
        bool PendingUpdate;
        void Update();
        void Update(transform _new);
        void UpdatePos(glm::vec3 _new);
    };
    struct RenderObject{
        mesh Mesh;
        transform Transform;
        int TextureID;
        int ShaderID;
        
        RenderObject();
        RenderObject(const char * path, int texture, int shader);
        ~RenderObject();
        void ApplyTransform();
    };
    
}