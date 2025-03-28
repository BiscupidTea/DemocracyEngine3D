#pragma once
#include "Entity2D.h"
#include "../Render/Renderer.h"

using namespace DemoEngine_Renderer;

namespace DemoEngine_Entities
{
	class EXPORT Shape : public Entity2D
	{
	private:

	public:
		Shape(vec3 newPosition, vec3 newRotation, vec3 newScale);
		~Shape();
	};
}
