#pragma once

#include "window.hpp"
#include "window_events.hpp"

namespace TE::App
{
	class Application
	{
		public:
			Application();
			~Application();

			void Run() const;
			void OnEvent(TE::Core::WindowHandle handle, TE::Core::Events& e);

		private:
			bool OnWindowClose(TE::Core::WindowHandle handle, TE::Core::EventWindowClose& e);

		private:
			TE::Core::IWindow* m_window{ nullptr };
			TE::Core::IWindow* m_window2{ nullptr };
	};
}