#pragma once
#include "../Tools/Export.h"
#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../Entities/Entity.h"

using namespace  glm;
using namespace DemoEngine_Entities;

class EXPORT Camera : public Entity
{
protected:
	mat4x4 proyection;
	mat4x4 view;
	
	vec3 LocalPosition;
	vec3 cameraFront;
	vec3 cameraUp;

public:
	Camera(vec2 aspect, float maxDistance, vec3 newPosition, vec3 newRotation, vec3 newScale);

	void Update();

	vec3 GetCameraPosition();
	vec3 GetCameraFoward();
	vec3 GetCameraRight();
	mat4x4 GetCameraProyection();
	mat4x4 GetCameraView();

	void SetCameraPosition(vec3 NewPosition);
	void TranslateCamera(vec3 dir);
	void RotateCamera(vec3 newRotation);
};