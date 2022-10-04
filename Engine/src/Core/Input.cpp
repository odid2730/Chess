#include "pch.h"
#include "Input.h"
#include "Application.h"

#include <GLFW/glfw3.h>

std::pair<int, int> Input::GetMousePos()
{
	double xpos, ypos;
	glfwGetCursorPos(static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()), &xpos, &ypos);
	return { (int)xpos, (int)ypos };
}

int Input::GetMouseX()
{
	auto& [xpos, ypos] = GetMousePos();
	return xpos;
}

int Input::GetMouseY()
{
	auto& [xpos, ypos] = GetMousePos();
	return ypos;
}
