#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
namespace Math{
    float lerp(float a, float b, float t);
    glm::vec2 lerp(glm::vec2 a, glm::vec2 b, float t);
    glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float t);
}