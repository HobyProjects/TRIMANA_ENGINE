#pragma once

#include <SDL3/SDL.h>
#include "base_window.hpp"

namespace TE::Core
{
	class SDL3_API final : public BaseAPI
	{
		public:
			SDL3_API() = default;
			virtual ~SDL3_API() = default;

			virtual bool Init() override;
			virtual void Quit() override;
			virtual BASE_APIS API() override { return API_SDL; }
	};

	class SDL3_Window final : public IWindow
	{
		public:
			SDL3_Window(const std::string& title, const std::shared_ptr<IContext>& context);
			virtual ~SDL3_Window();

			virtual Native Window() const override;
			virtual WindowProperties& Properties() override;
			virtual WindowHandle GetWindowHandle() override;

			virtual void SetEventsCallbackFunc(const std::function<void(WindowHandle, Events&)>&) override;
			virtual void PollEvents() override;
	};
}