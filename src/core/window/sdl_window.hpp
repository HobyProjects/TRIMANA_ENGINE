#pragma once

#include <SDL3/SDL.h>
#include "window.hpp"

namespace trimana::core {

	class sdl_service_api final : public platform_service_api {
	public:
		sdl_service_api() = default;
		virtual ~sdl_service_api() = default;

		virtual bool init() override;
		virtual void quit() override;
		virtual platform_service_apis api() override { return platform_service_apis::sdl_api; }

	private:
		bool m_initialized{ false };
	};

	class sdl_window final : public window {
	public:
		sdl_window(const std::string& title, const std::shared_ptr<sdl_service_api> sdl_api);
		virtual ~sdl_window();

		virtual void* native_window() const override { return m_window; }
		virtual window_properties* properties() override { return &m_properties; }
		virtual void swap_buffers() const override;

	private:
		SDL_Window* m_window{ nullptr };
		window_properties m_properties{};
		std::shared_ptr<context> m_context{ nullptr };
		std::weak_ptr<sdl_service_api> m_sdl_service_api;
	};
}