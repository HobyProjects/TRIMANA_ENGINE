#include "sdl_window.hpp"
#include "exceptions.hpp"
#include "renderer.hpp"
#include "log.hpp"

namespace TE::Core
{
	static bool s_Initialized{ false };

	bool SDL_API::Init()
	{
		if( !SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) )
		{
			throw UninitializedObjectException("Failed to initialize SDL");
			return ( s_Initialized = false );
		}

		TE_CORE_INFO("SDL initialized successfully");
		return ( s_Initialized = true );
	}

	void SDL_API::Quit()
	{
		if( s_Initialized )
		{
			SDL_Quit();
			s_Initialized = false;
		}
	}

	static SDL_Window* s_Window{ nullptr };
	static WindowProperties s_Properties{};

	_SDL_Window::_SDL_Window(const std::string& title)
	{
		const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
		if( mode != nullptr )
		{
			s_Properties.Width = mode->w;
			s_Properties.height = mode->h;
			s_Properties.FixedWidth = mode->w;
			s_Properties.FixedHeight = mode->h;
			s_Properties.MinWidth = 1024;
			s_Properties.MinHeight = 720;
			s_Properties.ColorBits.RedBit = 8;
			s_Properties.ColorBits.GreenBit = 8;
			s_Properties.ColorBits.BlueBit = 8;
			s_Properties.ColorBits.AlphaBit = 8;
			s_Properties.RefreshRate = mode->refresh_rate;
			s_Properties.ColorBits.DepthStencilBit = 8;
			s_Properties.ColorBits.DepthBit = 24;

		}
		else
		{
			TE_CORE_WARN("Failed to get display mode, using default values");
			s_Properties.Width = 1024;
			s_Properties.height = 720;
			s_Properties.FixedWidth = 0;
			s_Properties.FixedHeight = 0;
			s_Properties.MinWidth = 1024;
			s_Properties.MinHeight = 720;
			s_Properties.ColorBits.RedBit = 8;
			s_Properties.ColorBits.GreenBit = 8;
			s_Properties.ColorBits.BlueBit = 8;
			s_Properties.ColorBits.AlphaBit = 8;
			s_Properties.RefreshRate = 60;
			s_Properties.ColorBits.DepthStencilBit = 8;
			s_Properties.ColorBits.DepthBit = 24;
		}

		s_Properties.Title = title;

		if( Renderer::API() & RENDERER_API_OPENGL )
		{
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, s_Properties.ColorBits.RedBit);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, s_Properties.ColorBits.GreenBit);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, s_Properties.ColorBits.BlueBit);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, s_Properties.ColorBits.AlphaBit);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, s_Properties.ColorBits.DepthBit);
			SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, s_Properties.ColorBits.DepthStencilBit);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR_VERSION);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR_VERSION);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG);
		}

		SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;

		if( Renderer::API() & RENDERER_API_OPENGL )
		{
			window_flags |= SDL_WINDOW_OPENGL;
		}
		else if( Renderer::API() & RENDERER_API_VULKAN )
		{
			window_flags |= SDL_WINDOW_VULKAN;
		}
		else if( Renderer::API() & RENDERER_API_DIRECTX )
		{
			// window_flags |= SDL_WINDOW_DIRECT3D; // SDL_WINDOW_DIRECT3D is not a valid SDL window flag
		}

		s_Window = SDL_CreateWindow(s_Properties.Title.c_str(), s_Properties.MinWidth, s_Properties.MinHeight, window_flags);
		if( s_Window != nullptr )
		{
			TE_CORE_INFO("SDL window created successfully");
			SDL_SetWindowMinimumSize(s_Window, s_Properties.MinWidth, s_Properties.MinHeight);
			SDL_SetWindowMaximumSize(s_Window, s_Properties.FixedWidth, s_Properties.FixedHeight);
			SDL_GetWindowSizeInPixels(s_Window, &s_Properties.PixelWidth, &s_Properties.PixelHeight);

			s_Properties.IsActive = true;
			s_Properties.IsFocused = SDL_GetWindowFlags(s_Window) & SDL_WINDOW_INPUT_FOCUS;
			s_Properties.IsVSyncEnabled = true;
		}
		else
		{
			throw BaseAPIException("Failed to create SDL window");
			return;
		}
	}

	_SDL_Window::~_SDL_Window()
	{
		if( s_Window != nullptr )
		{
			SDL_DestroyWindow(s_Window);
			s_Window = nullptr;
		}
	}

	Native _SDL_Window::Window() const
	{
		return s_Window;
	}

	WindowProperties& _SDL_Window::Properties()
	{
		return s_Properties;
	}
}