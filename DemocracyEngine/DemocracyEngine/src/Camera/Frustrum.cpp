#include "Frustrum.h"

namespace DemoEngine_Camera
{
    void Frustum::Update(const mat4& viewProjectionMatrix)
    {
        // left
        planes[0] = {
            vec3(
                viewProjectionMatrix[0][3] + viewProjectionMatrix[0][0],
                viewProjectionMatrix[1][3] + viewProjectionMatrix[1][0],
                viewProjectionMatrix[2][3] + viewProjectionMatrix[2][0]),
            viewProjectionMatrix[3][3] + viewProjectionMatrix[3][0]
        };
        // right
        planes[1] = {
            vec3(
                viewProjectionMatrix[0][3] - viewProjectionMatrix[0][0],
                viewProjectionMatrix[1][3] - viewProjectionMatrix[1][0],
                viewProjectionMatrix[2][3] - viewProjectionMatrix[2][0]),
            viewProjectionMatrix[3][3] - viewProjectionMatrix[3][0]
        };
        // down
        planes[2] = {
            vec3(
                viewProjectionMatrix[0][3] + viewProjectionMatrix[0][1],
                viewProjectionMatrix[1][3] + viewProjectionMatrix[1][1],
                viewProjectionMatrix[2][3] + viewProjectionMatrix[2][1]),
            viewProjectionMatrix[3][3] + viewProjectionMatrix[3][1]
        };
        // Up
        planes[3] = {
            vec3(
                viewProjectionMatrix[0][3] - viewProjectionMatrix[0][1],
                viewProjectionMatrix[1][3] - viewProjectionMatrix[1][1],
                viewProjectionMatrix[2][3] - viewProjectionMatrix[2][1]),
            viewProjectionMatrix[3][3] - viewProjectionMatrix[3][1]
        };
        // Near
        planes[4] = {
            vec3(
                viewProjectionMatrix[0][3] + viewProjectionMatrix[0][2],
                viewProjectionMatrix[1][3] + viewProjectionMatrix[1][2],
                viewProjectionMatrix[2][3] + viewProjectionMatrix[2][2]),
            viewProjectionMatrix[3][3] + viewProjectionMatrix[3][2]
        };
        // Far
        planes[5] = {
            vec3(
                viewProjectionMatrix[0][3] - viewProjectionMatrix[0][2],
                viewProjectionMatrix[1][3] - viewProjectionMatrix[1][2],
                viewProjectionMatrix[2][3] - viewProjectionMatrix[2][2]),
            viewProjectionMatrix[3][3] - viewProjectionMatrix[3][2]
        };

        for (Plane& currentPlane : planes)
        {
            float vecLength = length(currentPlane.normal);
            currentPlane.normal /= vecLength;
            currentPlane.distance /= vecLength;
        }
    }

    bool Frustum::IsBoxVisible(const BoundingBox& box) const
    {
        // for (const auto& plane : planes)
        // {
        //     vec3 p_vertex = box.min;
        //     if (plane.normal.x >= 0) p_vertex.x = box.max.x;
        //     if (plane.normal.y >= 0) p_vertex.y = box.max.y;
        //     if (plane.normal.z >= 0) p_vertex.z = box.max.z;
        //
        //     if (plane.getSignedDistanceToPoint(p_vertex) < 0)
        //     {
        //         return false;
        //     }
        // }
        return true;
    }
}
