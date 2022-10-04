#pragma once

#include "Event.h"

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;

	static EventType GetStaticType() { return EventType::WindowClose; }
	virtual EventType GetEventType() override { return GetStaticType(); }
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowCloseEvent";
		return ss.str();
	}
};