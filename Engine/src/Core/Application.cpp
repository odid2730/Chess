#include "pch.h"
#include "Application.h"
#include "Input.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"

Application* Application::s_Instance = nullptr;

Application::Application()
{
	s_Instance = this;
	WindowProps props("Chess", 1200.0f, 720.0f);
	m_Window = Window::Create(props);
	m_Window->SetEventCallbackFn(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	RendererAPI::Init();
	Renderer::Init();

}

void Application::Run()
{
	m_LayerStack[2]->Activate(true); //Start layer

	while (m_Running)
	{
		m_Window->ClearColor();
		
		for (Layer* layer : m_LayerStack)
		{
			if (layer->IsActivate())
				layer->OnUpdate();
		}
		
		m_Window->SwapBuffer();
	}
	m_Layer->OnDetach();
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::GameStart()
{
	m_LayerStack[0]->Activate(true);  // Game layer activate
	m_LayerStack[1]->Activate(true);  // UI layer activate
	m_LayerStack[2]->Activate(false); // Start layer deactivate
}

void Application::ActivateSettings()
{
	m_LayerStack[3]->Activate(!m_LayerStack[3]->IsActivate());
}

void Application::ReturnToMenu()
{
	m_LayerStack[0]->Activate(false);  // Game layer deactivate
	m_LayerStack[1]->Activate(false);  // UI layer deactivate
	m_LayerStack[2]->Activate(true);   // Settings layer deactivate
	m_LayerStack[3]->Activate(false);   // Start layer activate;
}


void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MousePressedEvent>(std::bind(&Application::OnMousePressedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowCloseEvent, this, std::placeholders::_1));
	
	for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
	{
		if ((*it)->IsActivate() && e.Handled == false)
			(*it)->OnEvent(e);
	}
}

bool Application::OnMousePressedEvent(MousePressedEvent& e)
{
	// auto& [xpos, ypos] = Input::GetMousePos();
	// std::cout << "MousePressedEvent: MousePosition(" << xpos << ", " << ypos << ")" << std::endl;
	// return true;
	return false;
}

bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}
