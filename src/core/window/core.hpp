#pragma once

#include <string>
#include "base_window.hpp"

namespace TE::Core
{
	using Window = IWindow*;
	using Context = IContext;

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

			static void InitRenderer();
			static void QuitRenderer();

			static Window CreateWindow(const std::string& title);
			static void DestroyWindow(Window window);
			static std::shared_ptr<Context> GetContext();

			static BASE_APIS GetBaseAPI();
	};
}