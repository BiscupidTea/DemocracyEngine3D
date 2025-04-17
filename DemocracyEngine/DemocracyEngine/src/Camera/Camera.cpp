#include "Camera.h"

Camera::Camera(vec2 aspect, float maxDistance, vec3 newPosition, vec3 newRotation, vec3 newScale) : Entity(newPosition, newRotation, newScale)
{
	proyection = perspective(glm::radians(45.0f), aspect.x / aspect.y, 0.1f, maxDistance);

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

vec3 Camera::GetCameraFoward()
{
	return cameraFront;
}

vec3 Camera::GetCameraRight()
{
	return normalize(cross(cameraFront, vec3(0.0f,1.0f,0.0f)));
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
	LocalRotation = newRotation;

	float yaw = radians(LocalRotation.y);
	float pitch = radians(LocalRotation.x);
	float roll = radians(LocalRotation.z);

	vec3 front;
	front.x = cos(yaw) * cos(pitch);
	front.y = sin(pitch);
	front.z = sin(yaw) * cos(pitch);
	cameraFront = glm::normalize(front);

	vec3 right = glm::normalize(glm::cross(cameraFront, vec3(0.0f, 1.0f, 0.0f)));
	cameraUp = glm::normalize(glm::rotate(mat4(1.0f), roll, cameraFront) * vec4(0.0f, 1.0f, 0.0f, 1.0f));

	Update();
}
