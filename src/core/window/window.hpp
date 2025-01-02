#pragma once

#include "events.hpp"
#include "base_window.hpp"

namespace TE::Core
{
	class Core
	{
		private:
			Core() = default;
			Core(const Core&) = delete;
			Core& operator=(const Core&) = delete;
			~Core() = default;

		public:
			static bool Init();
			static void Quit();

			static bool HasActiveWindow();
			static IWindow* CreateWindow(const std::string& title);
			static void DestroyWindow(IWindow* window);
			static std::shared_ptr<IContext> GetContext();

			static void SetEventsCallbackFunc(const std::function<void(WindowHandle, Events&)>& callback);
			static void PollEvents();
			static void SwapBuffers();
	};
}