#pragma once

#include <glm/vec3.hpp>
#include <glm/common.hpp>
#include <limits>

namespace DemoEngine_Geometry
{
    using namespace glm;

    struct BoundingBox
    {
        vec3 min = vec3(std::numeric_limits<float>::max());
        vec3 max = vec3(std::numeric_limits<float>::lowest());

        BoundingBox() = default;

        BoundingBox(const vec3& pMin, const vec3& pMax) : min(pMin), max(pMax) {}

        void Expand(const vec3& point)
        {
            min = glm::min(min, point);
            max = glm::max(max, point);
        }

        void Expand(const BoundingBox& other)
        {
            min = glm::min(min, other.min);
            max = glm::max(max, other.max);
        }
    };
}