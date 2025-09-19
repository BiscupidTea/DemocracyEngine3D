#include "BoundingBox.h"
#include <limits>
#include <glm/glm.hpp>

namespace DemoEngine_Geometry
{
    BoundingBox::BoundingBox()
        : min(std::numeric_limits<float>::max()),
          max(std::numeric_limits<float>::lowest())
    {}

    BoundingBox::BoundingBox(const glm::vec3& min, const glm::vec3& max)
        : min(min), max(max)
    {}

    bool BoundingBox::IsValid() const
    {
        return (min.x <= max.x) && (min.y <= max.y) && (min.z <= max.z);
    }

    void BoundingBox::Expand(const glm::vec3& point)
    {
        min = glm::min(min, point);
        max = glm::max(max, point);
    }

    void BoundingBox::Expand(const BoundingBox& other)
    {
        if (!other.IsValid()) return;
        Expand(other.min);
        Expand(other.max);
    }

    BoundingBox BoundingBox::Transform(const glm::mat4& matrix) const
    {
        BoundingBox result;
        if (!IsValid()) return result;

        glm::vec3 corners[8] = {
            glm::vec3(min.x, min.y, min.z),
            glm::vec3(max.x, min.y, min.z),
            glm::vec3(min.x, max.y, min.z),
            glm::vec3(max.x, max.y, min.z),
            glm::vec3(min.x, min.y, max.z),
            glm::vec3(max.x, min.y, max.z),
            glm::vec3(min.x, max.y, max.z),
            glm::vec3(max.x, max.y, max.z)
        };

        for (int i = 0; i < 8; i++)
        {
            glm::vec4 transformed = matrix * glm::vec4(corners[i], 1.0f);
            result.Expand(glm::vec3(transformed));
        }

        return result;
    }

    BoundingBox BoundingBox::FromVertices(const std::vector<glm::vec3>& vertices)
    {
        BoundingBox box;
        for (const glm::vec3& v : vertices)
        {
            box.Expand(v);
        }
        return box;
    }
}
