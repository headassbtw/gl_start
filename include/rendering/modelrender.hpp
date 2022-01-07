#pragma once
#include <vector>
#include <glm/glm.hpp>
namespace model_render{
    void Bind_Buffers(std::vector<glm::vec3> vertices,std::vector<glm::vec2> uvs,std::vector<glm::vec3>normals);
    void Draw_Buffers(int prog1,int prog2, int end);
    void Prepare_Buffers();
    void Cleanup_Buffers(std::vector<glm::vec3> vertices,std::vector<glm::vec2> uvs,std::vector<glm::vec3>normals);
}