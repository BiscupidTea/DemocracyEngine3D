#include "Input.h"

namespace DemoEngine_Input
{
	Input::Input(Window* window)
	{
		this->window = window;
	}

	Input::~Input()
	{
	}

	bool Input::IsKeyPressed(int key)
	{
		return glfwGetKey(window->GetGLFWwindow(), key) == GLFW_PRESS;
	}

	bool Input::IsKeyReleased(int key)
	{
		return glfwGetKey(window->GetGLFWwindow(), key) == GLFW_RELEASE;
	}

	void Input::GetMouseDelta(float& deltaX, float& deltaY)
	{
		double xpos, ypos;
		glfwGetCursorPos(window->GetGLFWwindow(), &xpos, &ypos);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		deltaX = static_cast<float>(xpos - lastX);
		deltaY = static_cast<float>(lastY - ypos);

		lastX = xpos;
		lastY = ypos;
	}
}
