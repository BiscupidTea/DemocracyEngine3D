#pragma once
#include "Entity.h"

namespace DemoEngine_Entities
{
    class EXPORT Entity3D : public Entity
    {
    public:
        Entity3D(vec3 newPosition, vec3 newRotation, vec3 newScale);
        ~Entity3D();
    };
}
