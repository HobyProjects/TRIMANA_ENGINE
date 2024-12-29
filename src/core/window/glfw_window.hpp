#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "base_window.hpp"

namespace TE::Core
{
	class GLFW_API final : public BaseAPI
	{
		public:
			GLFW_API() = default;
			~GLFW_API() = default;

			virtual bool Init() override;
			virtual void Quit() override;
			virtual BASE_APIS API() override { return API_GLFW; }
	};

	class GLFW_Window final : public IWindow
	{
		public:
			GLFW_Window(const std::string& title);
			virtual ~GLFW_Window();

			virtual Native Window() const override;
			virtual WindowProperties& Properties() override;
	};
}