#pragma once

#include "Events/Event.h"

#include <GLFW/glfw3.h>

struct WindowProps
{
	std::string Title;
	uint32_t Width, Height;

	WindowProps(const std::string& title, uint32_t width, uint32_t height)
		: Title(title), Width(width), Height(height)
	{}
};

class Window
{
public:
	Window(const WindowProps& props);
	~Window();

	void ClearColor();
	void SwapBuffer();
	
	void SetEventCallbackFn(const std::function<void(Event&)> event) { m_WindowData.EventCallback = event; }

	void* GetNativeWindow() { return (void*)m_Window; }
	static std::unique_ptr<Window> Create(const WindowProps& props);
private:
	GLFWwindow* m_Window;

	struct WindowData
	{
		std::string Title;
		uint32_t Width, Height;

		std::function<void(Event&)> EventCallback;
	};

	WindowData m_WindowData;
};