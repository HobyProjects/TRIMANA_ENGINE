#pragma once

#include "window.hpp"
#include "window_events.hpp"
#include "keyboard_events.hpp"
#include "mouse_events.hpp"
#include "events_receiver.hpp"

namespace trimana::core {

	class sdl_events_receiver : public events_receiver {
	public:
		sdl_events_receiver(const std::shared_ptr<window>& window, const event_callback& callback);
		virtual ~sdl_events_receiver() = default;

		virtual void poll_events() const override;
	};
}