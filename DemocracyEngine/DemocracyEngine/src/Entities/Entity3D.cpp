#include "Entity3D.h"

#include <iostream>

namespace DemoEngine_Entities
{
    Entity3D::Entity3D(vec3 newPosition, vec3 newRotation, vec3 newScale): Entity(newPosition, newRotation, newScale)
    {
    }

    Entity3D::~Entity3D()
    {
        std::cout << "Delete Entity 3D" << '\n';
    }

    void Entity3D::setMaterial(Material material)
    {
        this->material = material;
    }
}
