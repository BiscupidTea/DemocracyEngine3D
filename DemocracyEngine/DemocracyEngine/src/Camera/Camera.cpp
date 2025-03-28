#include "Camera.h"

namespace DemoEngine_Renderer
{
	Camera::Camera(vec2 aspect, float maxDistance, vec3 position)
	{
		proyection = perspective(glm::radians(45.0f), aspect.x / aspect.y, 0.1f, maxDistance);

		LocalPosition = position;
		cameraFront = vec3(0.0f, 0.0f, -1.0f);
		cameraUp = vec3(0.0f, 1.0f, 0.0f);

		view = lookAt(LocalPosition, LocalPosition + cameraFront, cameraUp);
	}

	void Camera::Update()
	{
		view = lookAt(LocalPosition, LocalPosition + cameraFront, cameraUp);
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
		NewPosition.z = -NewPosition.z;
		LocalPosition = NewPosition;

		Update();
	}

	void Camera::TranslateCamera(vec3 dir)
	{
		dir.z = -dir.z;
		LocalPosition += dir;

		Update();
	}

	void Camera::RotateCamera(vec3 newRotation)
	{
		cameraFront = newRotation;

		Update();
	}
}