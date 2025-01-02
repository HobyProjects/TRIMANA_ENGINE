#pragma once

#include "events.hpp"
#include "base_window.hpp"

namespace TE::Core
{
	using Window = IWindow*;

	class Core
	{
		private:
			Core() = default;
			Core(const Core&) = delete;
			Core& operator=(const Core&) = delete;
			~Core() = default;

		public:
			static void Init();
			static void Quit();

			static Window CreateWindow(const std::string& title);
			static void DestroyWindow(Window window);
	};
}