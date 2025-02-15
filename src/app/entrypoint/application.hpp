#pragma once

#include "core.hpp"

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
			bool OnWindowResize(TE::Core::WindowHandle handle, TE::Core::EventWindowResize& e);

		private:
			TE::Core::Window m_window{ nullptr };
			TE::Core::Camera2D m_Camera{ 10.f, -1.0f, 1.0f };
			std::shared_ptr<TE::Core::Texture2D> m_Texture{ nullptr };
	};
}