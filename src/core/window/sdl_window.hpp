#pragma once

#include <SDL3/SDL.h>
#include "base_window.hpp"

namespace TE::Core
{
	class SDL_API final : public BaseAPI
	{
		public:
			SDL_API() = default;
			virtual ~SDL_API() = default;

			virtual bool Init() override;
			virtual void Quit() override;
			virtual BASE_APIS API() override { return API_SDL; }
	};

	class _SDL_Window final : public IWindow
	{
		public:
			_SDL_Window(const std::string& title);
			virtual ~_SDL_Window();

			virtual Native Window() const override;
			virtual WindowProperties& Properties() override;
	};
}