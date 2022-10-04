#pragma once

#include "Core/Layer.h"

#include "Renderer/Texture.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"

#include "Renderer/Camera.h"

#include <glm/glm.hpp>

class SettingsLayer : public Layer
{
public:
	SettingsLayer();
	virtual ~SettingsLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(Event& e) override;
private:
	std::shared_ptr<Texture> m_VolumnTexture, m_VolumnOn, m_VolumnOff, m_MenuTexture;
	bool OnMousePressed(MousePressedEvent& e);
private:
	float m_Volumn = 10.0f;

	Camera m_Camera;
};