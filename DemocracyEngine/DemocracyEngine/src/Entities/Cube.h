#pragma once
#include "Shape.h"

namespace DemoEngine_Entities
{
    class EXPORT Cube : public Shape
    {
    public:
        Cube(vec3 newPosition, vec3 newRotation, vec3 newScale);
        ~Cube();

        void Draw() override;
    };
}
