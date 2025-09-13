#pragma once

#include "../Scene/Plane.h"
#include <glm/vec3.hpp>
#include <glm/common.hpp>
#include <glm/mat4x4.hpp>
#include <array>
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

        BoundingBox Transform(const mat4& matrix) const
        {
            if (min.x > max.x) return {};

            std::array<vec3, 8> corners = {
                vec3(min.x, min.y, min.z), vec3(max.x, min.y, min.z),
                vec3(max.x, max.y, min.z), vec3(min.x, max.y, min.z),
                vec3(min.x, min.y, max.z), vec3(max.x, min.y, max.z),
                vec3(max.x, max.y, max.z), vec3(min.x, max.y, max.z)
            };

            BoundingBox transformedBox;
            for (const auto& corner : corners) {
                transformedBox.Expand(vec3(matrix * vec4(corner, 1.0f)));
            }
            return transformedBox;
        }

        vec3 GetCenter() const
        {
            return (min + max) * 0.5f;
        }

        bool Intersects(const BoundingBox& other) const
        {
            return (max.x >= other.min.x && min.x <= other.max.x) &&
                   (max.y >= other.min.y && min.y <= other.max.y) &&
                   (max.z >= other.min.z && min.z <= other.max.z);
        }

        bool IsOnOrBehindPlane(const Plane& plane) const
        {
            if (min.x > max.x) return false;
            
            vec3 positiveVertex = min;
            if (plane.normal.x >= 0) positiveVertex.x = max.x;
            if (plane.normal.y >= 0) positiveVertex.y = max.y;
            if (plane.normal.z >= 0) positiveVertex.z = max.z;
            
            return plane.getSignedDistanceToPoint(positiveVertex) <= 0;
        }
    };
}