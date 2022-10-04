#include "pch.h"
#include "SettingsLayer.h"

#include "Core/Application.h"
#include "Renderer/Renderer.h"

#include "GameData.h"
#include "Core/Mousecode.h"
#include "Utils/MousePicking.h"

SettingsLayer::SettingsLayer()
	: m_Camera(1200.0f, 720.0f, { 0.0f,0.0f,0.0f })
{
}

SettingsLayer::~SettingsLayer()
{
}

void SettingsLayer::OnAttach()
{
	m_VolumnTexture = Texture::Create("assets/textures/volumn.png");
	m_VolumnOn = Texture::Create("assets/textures/volumn_on.png");
	m_VolumnOff = Texture::Create("assets/textures/volumn_off.png");
	m_MenuTexture = Texture::Create("assets/textures/menu.png");
}

void SettingsLayer::OnDetach()
{
}

void SettingsLayer::OnUpdate()
{
	Renderer::BeginScene(m_Camera);

	Renderer::DrawFixedQuad({ 0.0f, 0.0f, 0.8f }, { 0.3f, 0.3f, 0.3f, 0.8f }, { (1200.0f / 720.0f) * 10.0f, 10.0f });

	// Volumn adjust
	Renderer::DrawFixedQuad({ -2.0f, 3.0f, 0.9f }, m_VolumnTexture, { 2.0f, 1.0f });
	Renderer::DrawFixedQuad({ -0.5f, 3.0f, 0.9f }, m_Volumn != 0 ? m_VolumnOn : m_VolumnOff, { 0.5f, 0.5f }, 152);
	for (int i = 0; i < 10; i++)
	{
		if (i < m_Volumn)
			Renderer::DrawFixedQuad({ 0.0f + 0.24f * i, 3.0f, 0.9f }, { 0.427f, 0.968f, 0.914f, 1.0f }, { 0.2f, 0.7f }, 153 + i);
		else
			Renderer::DrawFixedQuad({ 0.0f + 0.24f * i, 3.0f, 0.9f }, { 0.427f, 0.968f, 0.914f, 0.3f }, { 0.2f, 0.7f }, 153 + i);
	}
	// Return to menu
	Renderer::DrawFixedQuad({ 0.0f, -3.0f, 0.9f }, m_MenuTexture, { 2.0f, 1.0f }, 170); // TODO: fix stencil
	
	Renderer::EndScene();
}

void SettingsLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MousePressedEvent>(std::bind(&SettingsLayer::OnMousePressed, this, std::placeholders::_1));
}

bool SettingsLayer::OnMousePressed(MousePressedEvent& e)
{
	int stencil = Utils::GetStencilIndex();

	GameData::AudioData& audioData = GameData::GetAudioData();

	if (e.GetMouseButton() == MOUSE_BUTTON_LEFT)
	{
		if (stencil >= 152 && stencil <= 162)
		{
			m_Volumn = stencil - 153 + 1;
			audioData.SetVolumn(m_Volumn / 10.0f);
		}
		switch (stencil)
		{
			// Return to menu
			case 170:
			{
				Application& app = Application::Get();
				app.ReturnToMenu();
				break;
			}
		}
	}
	return true;
}
