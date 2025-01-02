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

			static IWindow* CreateWindow(const std::string& title);
			static void DestroyWindow(IWindow* window);
	};
}