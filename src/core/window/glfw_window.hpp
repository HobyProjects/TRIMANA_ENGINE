#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "base_window.hpp"

namespace TE::Core
{
	class GLFW3_API final : public BaseAPI
	{
		public:
			GLFW3_API() = default;
			~GLFW3_API() = default;

			virtual bool Init() override;
			virtual void Quit() override;
			virtual BASE_APIS API() override { return API_GLFW; }
	};

	class GLFW3_Window final : public IWindow
	{
		public:
			GLFW3_Window(const std::string& title, const std::shared_ptr<IContext> context);
			virtual ~GLFW3_Window();

			virtual bool IsActive() const override;
			virtual Native Window() const override;
			virtual WindowProperties& Properties() override;
			virtual WindowHandle GetWindowHandle() override;
			virtual void PollEvents() override;
			virtual void SwapBuffers() override;
			virtual void SetEventsCallbackFunc(const std::function<void(WindowHandle, Events&)>&) override;
	};
}