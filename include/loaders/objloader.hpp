#pragma once
#include <glm/glm.hpp>
#include <vector>
namespace Loaders{
    namespace Models{
        bool loadOBJ(
            const char * path,
            std::vector < glm::vec3 > & out_vertices,
            std::vector < glm::vec2 > & out_uvs,
            std::vector < glm::vec3 > & out_normals
        );
        bool loadCOB(
            const char * path,
            std::vector < glm::vec3 > & out_vertices,
            std::vector < glm::vec2 > & out_uvs,
            std::vector < glm::vec3 > & out_normals
        );
    }
}