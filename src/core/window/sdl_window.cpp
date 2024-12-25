#include "sdl_window.hpp"
#include "exceptions.hpp"
#include "renderer.hpp"
#include "log.hpp"

namespace trimana::core {

	bool sdl_service_api::init() {
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
			throw uninitialized_object_exception("Failed to initialize SDL");
			return (m_initialized = false);
		}

		TRIMANA_CORE_INFO("SDL initialized successfully");
		return (m_initialized = true);
	}

	void sdl_service_api::quit() {
		if (m_initialized) {
			SDL_Quit();
			m_initialized = false;
		}
	}

	sdl_window::sdl_window(const std::string& title) {
		const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
		if (mode != nullptr) {
			m_properties.width = mode->w;
			m_properties.height = mode->h;
			m_properties.fixed_width = mode->w;
			m_properties.fixed_height = mode->h;
			m_properties.min_width = 1024;
			m_properties.min_height = 720;
			m_properties.red_color_bits = 8;
			m_properties.green_color_bits = 8;
			m_properties.blue_color_bits = 8;
			m_properties.alpha_color_bits = 8;
			m_properties.refresh_rate = mode->refresh_rate;
			m_properties.stencil_color_bits = 8;
			m_properties.depth_color_bits = 24;

		}
		else {
			TRIMANA_CORE_WARN("Failed to get display mode, using default values");
			m_properties.width = 1280;
			m_properties.height = 720;
			m_properties.fixed_width = 0;
			m_properties.fixed_height = 0;
			m_properties.min_width = 1024;
			m_properties.min_height = 720;
			m_properties.red_color_bits = 8;
			m_properties.green_color_bits = 8;
			m_properties.blue_color_bits = 8;
			m_properties.alpha_color_bits = 8;
			m_properties.refresh_rate = 60;
			m_properties.stencil_color_bits = 8;
			m_properties.depth_color_bits = 24;
		}

		m_properties.title = title;

		if(renderer::api() == rendering_api::opengl){
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, m_properties.red_color_bits);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, m_properties.green_color_bits);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, m_properties.blue_color_bits);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, m_properties.alpha_color_bits);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, m_properties.depth_color_bits);
			SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, m_properties.stencil_color_bits);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, static_cast<uint32_t>(rendering_context_version::opengl_api_major_version));
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, static_cast<uint32_t>(rendering_context_version::opengl_api_minor_version));
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG);
		}

		SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;

		if(renderer::api() == rendering_api::opengl){
			window_flags |= SDL_WINDOW_OPENGL;
		}
		else if(renderer::api() == rendering_api::vulkan){
			window_flags |= SDL_WINDOW_VULKAN;
		}
		else if(renderer::api() == rendering_api::directx){
			// window_flags |= SDL_WINDOW_DIRECT3D; // SDL_WINDOW_DIRECT3D is not a valid SDL window flag
		}

		m_window = SDL_CreateWindow(m_properties.title.c_str(), m_properties.width, m_properties.height, window_flags);
		if(m_window != nullptr){
			TRIMANA_CORE_INFO("SDL window created successfully");
		}
		
		throw api_response_exception("Failed to create SDL window");
		SDL_Quit();
	}
}