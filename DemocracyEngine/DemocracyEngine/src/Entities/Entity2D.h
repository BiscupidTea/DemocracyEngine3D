#pragma once
#include "Entity.h"

namespace DemoEngine_Entities
{
    class EXPORT Entity2D : public Entity
    {
    public:
        Entity2D(vec3 newPosition, vec3 newRotation, vec3 newScale);
        ~Entity2D();
    };
}
