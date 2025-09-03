#pragma once

#include <glm/glm.hpp>
#include <array>
#include "../Mesh/BoundingBox.h"

namespace DemoEngine_Camera
{
    using namespace glm;
    using namespace DemoEngine_Geometry;

    struct Plane
    {
        vec3 normal = { 0.f, 1.f, 0.f };
        float distance = 0.f;

        float getSignedDistanceToPoint(const vec3& point) const
        {
            return dot(normal, point) + distance;
        }
    };

    class Frustum
    {
    public:
        std::array<Plane, 6> planes;

        void Update(const mat4& viewProjectionMatrix);
        bool IsBoxVisible(const BoundingBox& box) const;
    };
}