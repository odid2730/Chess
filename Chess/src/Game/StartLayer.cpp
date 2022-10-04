#include "pch.h"
#include "StartLayer.h"

#include "Core/Application.h"
#include "Renderer/Renderer.h"

#include "Utils/MousePicking.h"
#include "Core/MouseCode.h"

#include <glm/glm.hpp>

StartLayer::StartLayer()
	: m_Camera(1200.0f, 720.0f, { 0.0f, 0.0f, 0.0f })
{
}

void StartLayer::OnAttach()
{
	m_BackgroundTexture = Texture::Create("assets/textures/StartLayer/background.png");
	m_GameStartTexture = Texture::Create("assets/textures/StartLayer/gamestart.png");
	m_SettingsTexture = Texture::Create("assets/textures/StartLayer/settings.png");
}

void StartLayer::OnDetach()
{
}

void StartLayer::OnUpdate()
{
	Renderer::BeginScene(m_Camera);

	//Renderer::DrawQuad({ 0.0f,0.0f,0.0f }, { 0.8f,0.3f,0.2f, 1.0f }, { 1.0f,1.0f });
	Renderer::DrawQuad({ 0.0f, 0.0f, 0.0f }, m_BackgroundTexture, { (1200.0f / 720.0f) * 10.0f,10.0f });
	Renderer::DrawQuad({ -4.0f, -3.0f, 0.1f }, m_GameStartTexture, { 5.0f,2.5f }, 150);
	Renderer::DrawQuad({ 4.0f, -3.0f, 0.1f }, m_SettingsTexture, { 5.0f,2.5f }, 151);

	Renderer::EndScene();
}

void StartLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MousePressedEvent>(std::bind(&StartLayer::OnMousePressed, this, std::placeholders::_1));
}

bool StartLayer::OnMousePressed(MousePressedEvent& e)
{
	int stencil = Utils::GetStencilIndex();

	if (e.GetMouseButton() == MOUSE_BUTTON_LEFT)
	{
		switch (stencil)
		{
			// GameStart
			case 150:
			{
				Application& app = Application::Get();
				app.GameStart();
				break;
			}
			// Settings
			case 151:
			{
				Application& app = Application::Get();
				app.ActivateSettings();
				break;
			}
		}
	}
	return true;
}
