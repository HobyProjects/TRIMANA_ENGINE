#pragma once

#include "events_receiver.hpp"

namespace trimana::core
{
	class glfw_events_receiver : public events_receiver
	{
	public:
		glfw_events_receiver(const std::shared_ptr<window>& win, const event_callback& callback);
		virtual ~glfw_events_receiver() = default;

		virtual void poll_events() const override;
	};
}