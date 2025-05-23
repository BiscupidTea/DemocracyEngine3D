#include "Entity2D.h"

#include <iostream>

namespace DemoEngine_Entities
{
	Entity2D::Entity2D(vec3 newPosition, vec3 newRotation, vec3 newScale): Entity(newPosition, newRotation, newScale)
	{
	}

	Entity2D::~Entity2D()
	{
		std::cout << "Delete Entity 2D" << '\n';
	}
}
