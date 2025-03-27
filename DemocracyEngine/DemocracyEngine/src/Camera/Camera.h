#pragma once
#include "../Tools/Export.h"
#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

using namespace  glm;

namespace DemoEngine_Renderer
{
	class EXPORT Camera
	{
	private:
		mat4x4 proyection;
		mat4x4 view;
		vec3 LocalPosition;

	public:
		Camera(vec2 aspect, float maxDistance, vec3 position = vec3 {0,0,0});
		
		void Update();
		
		vec3 GetCameraPosition();
		mat4x4 GetCameraProyection();
		mat4x4 GetCameraView();
		
		void SetCameraPosition(vec3 NewPosition);
		void TranslateCamera(vec3 dir);
	};

}