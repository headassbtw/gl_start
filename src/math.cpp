#include <glm/ext/vector_float3.hpp>
#include <math.hpp>

using namespace Math;

float Math::lerp(float a, float b, float t){
    return a + t * (b-a);
}
glm::vec2 Math::lerp(glm::vec2 a, glm::vec2 b, float t){
    return glm::vec2(
        lerp(a.x,b.x,t),
        lerp(a.x,b.x,t)
    );
}
glm::vec3 Math::lerp(glm::vec3 a, glm::vec3 b, float t){
    return glm::vec3(
        lerp(a.x,b.x,t),
        lerp(a.x,b.x,t),
        lerp(a.x,b.x,t)
    );
}