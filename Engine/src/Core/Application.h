#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Layer.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

class Application
{
public:
	Application();
	virtual ~Application() = default;

	void Run();
	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void GameStart();
	void ActivateSettings();
	void ReturnToMenu();

	static Application& Get() { return *s_Instance; }
	Window& GetWindow() { return *m_Window; }
private:
	bool OnMousePressedEvent(MousePressedEvent& e);
	bool OnWindowCloseEvent(WindowCloseEvent& e);
private:
	bool m_Running = true;
	LayerStack m_LayerStack;
	Layer* m_Layer;
	std::unique_ptr<Window> m_Window;

	static Application* s_Instance;
};

Application* CreateApp();