#pragma once

#include "window.hpp"
#include "window_events.hpp"
#include "keyboard_events.hpp"
#include "mouse_events.hpp"

namespace trimana::core {

	class events_receiver {
	public:
		events_receiver() = default;
		virtual ~events_receiver() = default;

		virtual void poll_events() const = 0;

	public:
		class events_receiver_builder {
		private:
			events_receiver_builder() = default;
			~events_receiver_builder() = default;

		public:
			static std::shared_ptr<events_receiver> create(const std::shared_ptr<window>& window, const event_callback& callback);
		};
	};
}