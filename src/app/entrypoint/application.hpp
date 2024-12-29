#pragma once

#include "window.hpp"
#include "events_receiver.hpp"

namespace TE::app
{
	class application
	{
		public:
			application();
			~application();

			void run() const;
			void on_events(TE::Core::Events& e);

		private:
			bool on_window_close(TE::Core::window_close_event& e);

		private:
			std::shared_ptr<TE::Core::base_window> m_window{ nullptr };
			std::shared_ptr<TE::Core::events_receiver> m_events_receiver{ nullptr };
	};
}