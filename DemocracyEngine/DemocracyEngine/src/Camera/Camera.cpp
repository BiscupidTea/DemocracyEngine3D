#include "Camera.h"

namespace DemoEngine_Renderer
{
	Camera::Camera(vec2 aspect, float maxDistance, vec3 position)
	{
		proyection = perspective(glm::radians(45.0f), aspect.x / aspect.y, 0.1f, maxDistance);

		LocalPosition = position;

		view = lookAt(LocalPosition, LocalPosition + vec3(0.0f, 0.0f, -1.0f), { 0,1,0 });
	}

	void Camera::Update()
	{
		view = lookAt(LocalPosition, LocalPosition + vec3(0.0f, 0.0f, -1.0f), { 0,1,0 });
	}

	vec3 Camera::GetCameraPosition()
	{
		return LocalPosition;
	}

	mat4x4 Camera::GetCameraProyection()
	{
		return proyection;
	}

	mat4x4 Camera::GetCameraView()
	{
		return view;
	}

	void Camera::SetCameraPosition(vec3 NewPosition)
	{
		LocalPosition = NewPosition;
	}

	void Camera::TranslateCamera(vec3 dir)
	{
		LocalPosition += dir;
	}
}