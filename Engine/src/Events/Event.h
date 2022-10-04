#pragma once

#include <string>
#include <sstream>

enum class EventType
{
	KeyPressed,
	MousePressed, MouseReleased,
	WindowClose
};

class Event
{
public:
	bool Handled = false;

	virtual EventType GetEventType() = 0;
	virtual std::string ToString() const = 0;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& e)
		: m_Event(e)
	{}

	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.Handled = func(static_cast<T&>(m_Event));
			return true;
		}
		return false;
	}
private:
	Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}