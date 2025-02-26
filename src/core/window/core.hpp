#pragma once

#include <string>
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
			static void Init();
			static void Quit();

			static void InitRenderer();
			static void QuitRenderer();
			static float GetSystemTicks();

			static std::shared_ptr<IWindow> CreateWindow(const std::string& title);
			static std::shared_ptr<IContext> GetContext();

			static BASE_APIS GetBaseAPI();
	};
}