#pragma once

#include "Event.h"

class KeyEvent : public Event
{
public:
	KeyEvent(int keycode)
		: m_Keycode(keycode)
	{}

	inline int GetKeycode() const { return m_Keycode; }
protected:
	int m_Keycode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int keycode)
		: KeyEvent(keycode)
	{}
	static EventType GetStaticType() { return EventType::KeyPressed; }
	virtual EventType GetEventType() override { return GetStaticType(); }
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_Keycode;
		return ss.str();
	}
};