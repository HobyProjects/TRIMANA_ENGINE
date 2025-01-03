#pragma once

#include "trimana_core.hpp"

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
			TE::Core::Window m_window{ nullptr };
	};
}