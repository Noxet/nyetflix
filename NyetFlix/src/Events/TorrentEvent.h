#pragma once

#include "Event.h"

namespace nyetflix
{
	class TorrentAddedEvent : public Event
	{
	public:
		TorrentAddedEvent() = default;

		EVENT_CLASS_TYPE(TorrentAdded)
	};
}
