#pragma once

#include "Event.h"

class MouseEvent : public Event
{
public:
	MouseEvent(int button)
		: m_Button(button)
	{

	}

	inline int GetMouseButton() const { return m_Button; }

protected:
	int m_Button;
};

class MousePressedEvent : public MouseEvent
{
public:
	MousePressedEvent(int button)
		: MouseEvent(button)
	{}

	static EventType GetStaticType() { return EventType::MousePressed; }
	virtual EventType GetEventType() override { return GetStaticType(); }
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MousePressedEvent: " << m_Button;
		return ss.str();
	}
};

class MouseReleasedEvent : public MouseEvent
{
public:
	MouseReleasedEvent(int button)
		: MouseEvent(button)
	{}

	static EventType GetStaticType() { return EventType::MouseReleased; }
	virtual EventType GetEventType() override { return GetStaticType(); }
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseReleasedEvent: " << m_Button;
		return ss.str();
	}
};