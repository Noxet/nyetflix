#pragma once
#include <string>

namespace nyetflix
{
	enum class EventType
	{
		TorrentAdded, TorrentFinished
	};


#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; } \
	virtual EventType getEventType() const override { return getStaticType(); }\
	virtual std::string getName() const override { return #type; }


	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType getEventType() const = 0;
		virtual std::string getName() const = 0;
	};
}
