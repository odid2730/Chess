#include "pch.h"
#include "Window.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include <glad/glad.h>

Window::Window(const WindowProps& props)
{
	m_WindowData.Title = props.Title;
	m_WindowData.Width = props.Width;
	m_WindowData.Height = props.Height;

	if (!glfwInit())
	{
		std::cout << "Glfw initialization error" << std::endl;
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	m_Window = glfwCreateWindow(1200.0f, 720.0f, "Chess", NULL, NULL);
	if (!m_Window)
	{
		std::cout << "glfw window creation error" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Glad initialization error" << std::endl;
	}
	
	glfwSetWindowUserPointer(m_Window, &m_WindowData);

	glfwSetErrorCallback([](int error_code, const char* description) {
		std::cout << "Error code(" << error_code << "): " << description << std::endl;
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		
		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent e(key);
				data.EventCallback(e);
				break;
			}
		}
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				MousePressedEvent e(button);
				data.EventCallback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseReleasedEvent e(button);
				data.EventCallback(e);
				break;
			}
		}
	});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.EventCallback(event);
	});

}

Window::~Window()
{
}

void Window::ClearColor()
{
	glClearColor(0.96f, 0.96f, 0.863f, 1.0f);
	//glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glEnable(GL_STENCIL_TEST);
	//glStencilMask(0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//glStencilFunc(GL_GREATER, 1, -1);
}

void Window::SwapBuffer()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

std::unique_ptr<Window> Window::Create(const WindowProps& props)
{
	return std::unique_ptr<Window>(new Window(props));
}
