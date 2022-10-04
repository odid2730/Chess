#pragma once

#include "Events/Event.h"

class Layer
{
public:
	Layer() = default;
	virtual ~Layer() = default;

	virtual void OnAttach() = 0;
	virtual void OnDetach() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnEvent(Event& e) {};

	void Activate(bool activate) { m_Activated = activate; }
	bool IsActivate() { return m_Activated; }
private:
	bool m_Activated = false;
};