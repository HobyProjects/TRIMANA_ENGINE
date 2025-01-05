#include "core_pch.hpp"

namespace TE::Core
{
	static bool s_Initialized{ false };
	static SDL_Event s_Event{};
	static std::function<void(WindowHandle, Events&)> s_CallbackFunc{nullptr};

	bool SDL3_API::Init()
	{
		if( !SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) )
		{
			throw UninitializedObjectException("Failed to initialize SDL");
			return ( s_Initialized = false );
		}

		TE_CORE_INFO("SDL initialized successfully");
		return ( s_Initialized = true );
	}

	void SDL3_API::Quit()
	{
		if( s_Initialized )
		{
			SDL_Quit();
			s_Initialized = false;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	static SDL_Window* s_Window{ nullptr };
	static WindowProperties s_Properties{};
	static std::weak_ptr<IContext> s_Context{};

	SDL3_Window::SDL3_Window(const std::string& title, const std::shared_ptr<IContext>& context)
	{
		s_Context = context;
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
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, RENDERER_GL_MAJOR_VERSION);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, RENDERER_GL_MINOR_VERSION);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG);
		}

		SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;

		if( Renderer::API() & RENDERER_API_OPENGL )
		{
			window_flags |= SDL_WINDOW_OPENGL;
		}

		if( Renderer::API() & RENDERER_API_VULKAN )
		{
			window_flags |= SDL_WINDOW_VULKAN;
		}

		if( Renderer::API() & RENDERER_API_DIRECTX )
		{
			//[TODO]: Need to find what is the enum flag for DirectX
		}

		s_Window = SDL_CreateWindow(s_Properties.Title.c_str(), s_Properties.MinWidth, s_Properties.MinHeight, window_flags);
		if( s_Window != nullptr )
		{
			TE_CORE_INFO("SDL window created successfully");
			SDL_SetWindowMinimumSize(s_Window, s_Properties.MinWidth, s_Properties.MinHeight);
			SDL_SetWindowMaximumSize(s_Window, s_Properties.FixedWidth, s_Properties.FixedHeight);
			SDL_GetWindowSizeInPixels(s_Window, &s_Properties.PixelWidth, &s_Properties.PixelHeight);

			if( !s_Context.expired() )
			{
				auto context = s_Context.lock();
				context->Attach(s_Window);
			}

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

	SDL3_Window::~SDL3_Window()
	{
		if( s_Window != nullptr )
		{
			SDL_DestroyWindow(s_Window);
			s_Window = nullptr;
		}
	}

	bool SDL3_Window::IsActive() const
	{
		return s_Properties.IsActive;
	}

	Native SDL3_Window::Window() const
	{
		return s_Window;
	}

	WindowProperties& SDL3_Window::Properties()
	{
		return s_Properties;
	}

	WindowHandle SDL3_Window::GetWindowHandle()
	{
		return s_Properties.Handle;
	}

	void SDL3_Window::SetEventsCallbackFunc(const std::function<void(WindowHandle, Events&)>& callbackFunc)
	{
		s_CallbackFunc = callbackFunc;
	}

	void SDL3_Window::PollEvents()
	{
		SDL_WaitEvent(&s_Event);

		switch( s_Event.type )
		{
			case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			{
				EventWindowClose windowCloseEvent;
				s_CallbackFunc(s_Properties.Handle, windowCloseEvent);
				break;
			}
			case SDL_EVENT_WINDOW_RESIZED:
			{
				EventWindowResize windowResizedEvent(s_Event.window.data1, s_Event.window.data2);
				s_Properties.Width = s_Event.window.data1;
				s_Properties.height = s_Event.window.data2;
				s_CallbackFunc(s_Properties.Handle, windowResizedEvent);
				break;
			}
			case SDL_EVENT_WINDOW_MINIMIZED:
			{
				EventWindowMinimize windowMinimizedEvent;
				s_Properties.WindowState = WINDOW_MINIMIZED;
				s_CallbackFunc(s_Properties.Handle, windowMinimizedEvent);
				break;
			}
			case SDL_EVENT_WINDOW_MAXIMIZED:
			{
				EventWindowMaximaize windowMaximizedEvent;
				s_Properties.WindowState = WINDOW_MAXIMIZED;
				s_CallbackFunc(s_Properties.Handle, windowMaximizedEvent);
				break;
			}
			case SDL_EVENT_WINDOW_RESTORED:
			{
				EventWindowRestore windowRestoredEvent;
				s_Properties.WindowState = WINDOW_NORMAL;
				s_CallbackFunc(s_Properties.Handle, windowRestoredEvent);
				break;
			}
			case SDL_EVENT_WINDOW_FOCUS_GAINED:
			{
				EventWindowFocusGain windowFocusGainedEvent;
				s_Properties.IsFocused = true;
				s_CallbackFunc(s_Properties.Handle, windowFocusGainedEvent);
				break;
			}
			case SDL_EVENT_WINDOW_FOCUS_LOST:
			{
				EventWindowFocusLost windowFocusLostEvent;
				s_Properties.IsFocused = false;
				s_CallbackFunc(s_Properties.Handle, windowFocusLostEvent);
				break;
			}
			case SDL_EVENT_WINDOW_MOVED:
			{
				EventWindowPosChange windowMovedEvent(s_Event.window.data1, s_Event.window.data2);
				s_Properties.PosX = s_Event.window.data1;
				s_Properties.PosY = s_Event.window.data2;
				s_CallbackFunc(s_Properties.Handle, windowMovedEvent);
				break;
			}
			case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
			{
				EventWindowPixelSizeChange windowPixelSizeChangedEvent(s_Event.window.data1, s_Event.window.data2);
				s_Properties.PixelWidth = s_Event.window.data1;
				s_Properties.PixelHeight = s_Event.window.data2;
				s_CallbackFunc(s_Properties.Handle, windowPixelSizeChangedEvent);
				break;
			}
			case SDL_EVENT_KEY_DOWN:
			{
				if( s_Event.key.down )
				{
					EventKeyboardKeyPress keyPress(static_cast<KEY>( s_Event.key.key ));
					s_CallbackFunc(s_Properties.Handle, keyPress);
					break;
				}

				if( s_Event.key.repeat )
				{
					EventKeyboardKeyRepeate keyRepeate(static_cast<KEY>( s_Event.key.key ));
					s_CallbackFunc(s_Properties.Handle, keyRepeate);
					break;
				}

				break;
			}
			case SDL_EVENT_KEY_UP:
			{
				EventKeyboardKeyRelease keyRelease(static_cast<KEY>( s_Event.key.key ));
				s_CallbackFunc(s_Properties.Handle, keyRelease);
				break;
			}
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
			{
				EventMouseButtonDown mouseButtonPress(static_cast<MOUSE_BUTTON>( s_Event.button.button ));
				s_CallbackFunc(s_Properties.Handle, mouseButtonPress);
				break;
			}
			case SDL_EVENT_MOUSE_BUTTON_UP:
			{
				EventMouseButtonUp mouseButtonRelease(static_cast<MOUSE_BUTTON>( s_Event.button.button ));
				s_CallbackFunc(s_Properties.Handle, mouseButtonRelease);
				break;
			}
			case SDL_EVENT_MOUSE_MOTION:
			{
				EventMouseCursorMove mouseMove(s_Event.motion.x, s_Event.motion.y);
				s_CallbackFunc(s_Properties.Handle, mouseMove);
				break;
			}
			case SDL_EVENT_MOUSE_WHEEL:
			{
				EventMouseWheelScroll mouseScroll(s_Event.wheel.x, s_Event.wheel.y);
				s_CallbackFunc(s_Properties.Handle, mouseScroll);
				break;
			}
			case SDL_EVENT_WINDOW_MOUSE_ENTER:
			{
				EventMouseCursorWindowEnter mouseEnter;
				s_CallbackFunc(s_Properties.Handle, mouseEnter);
				break;
			}
			case SDL_EVENT_WINDOW_MOUSE_LEAVE:
			{
				EventMouseCursorWindowLeave mouseLeave;
				s_CallbackFunc(s_Properties.Handle, mouseLeave);
				break;
			}
			default:
			{
				break;
			}
		}
	}

	void SDL3_Window::SwapBuffers()
	{
		if( !s_Context.expired() )
		{
			auto context = s_Context.lock();
			context->SwapBuffers(s_Window);
		}
	}
}