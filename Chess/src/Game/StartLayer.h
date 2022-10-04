#pragma once

#include "Core/Layer.h"

#include "Renderer/Texture.h"

#include "Events/Event.h"
#include "Events/MouseEvent.h"

#include "Renderer/Camera.h"

class StartLayer : public Layer
{
public:
	StartLayer();
	virtual ~StartLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(Event & e) override;
private:
	bool OnMousePressed(MousePressedEvent& e);
private:
	std::shared_ptr<Texture> m_BackgroundTexture = nullptr;
	std::shared_ptr<Texture> m_GameStartTexture = nullptr;
	std::shared_ptr<Texture> m_SettingsTexture = nullptr;
	Camera m_Camera;
};