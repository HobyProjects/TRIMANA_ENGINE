#include <mutex>
#include <unordered_map>

#include "window.hpp"
#include "exceptions.hpp"
#include "renderer.hpp"

#include "opengl/glfw_gl_context.hpp"
#include "opengl/sdl_gl_context.hpp"

#include "glfw_window.hpp"
#include "sdl_window.hpp"


namespace TE::Core
{
	static bool s_CoreInitialized = false;

	/**********************************************
	*		  INITIALIZING BASE API			      *
	***********************************************/

	static std::shared_ptr<BaseAPI> s_BaseAPI;

	static BASE_APIS GetPlatformBaseAPI()
	{
		#if defined(TE_PLATFORM_WINDOWS)

		//return base_api::win32_api;
		return API_GLFW;

		#elif defined(TE_PLATFORM_LINUX)

		return API_SDL;

		#else

		return API_GLFW;

		#endif
	}

	static void InitBaseAPI()
	{
		switch( GetPlatformBaseAPI() )
		{
			case API_GLFW:
			{
				s_BaseAPI = std::make_shared<GLFW3_API>();
				if( !s_BaseAPI->Init() )
					throw UninitializedObjectException("Failed to initialize the base API : GLFW");

				break;
			}
			case API_SDL:
			{
				s_BaseAPI = std::make_shared<SDL3_API>();
				if( !s_BaseAPI->Init() )
					throw UninitializedObjectException("Failed to initialize the base API : SDL");

				break;
			}
			case API_WIN32:
			{
				throw UnimplementedFeatureException("Win32 API is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	/**********************************************
	*		      WINDOW HANDLING			      *
	***********************************************/

	static std::shared_ptr<IContext> s_Context;
	static std::unordered_map<WindowHandle, IWindow*> s_WindowPool;

	static WindowHandle GetUniqueHandle()
	{
		static WindowHandle s_Handle = 0;
		return s_Handle++;
	}

	static void InitContext()
	{
		switch( GetPlatformBaseAPI() )
		{
			case API_GLFW:
			{
				switch( Renderer::API() )
				{
					case RENDERER_API_OPENGL:
					{
						s_Context = std::make_shared<GLFW_GL_Context>();
						break;
					}
					case RENDERER_API_VULKAN:
					{
						throw UnimplementedFeatureException("Vulkan API is not implemented yet");
						break;
					}
					case RENDERER_API_DIRECTX:
					{
						throw UnimplementedFeatureException("DirectX API is not implemented yet");
						break;
					}
					default:
					{
						break;
					}
				};

				break;
			}
			case API_SDL:
			{
				switch( Renderer::API() )
				{
					case RENDERER_API_OPENGL:
					{
						s_Context = std::make_shared<SDL_GL_Context>();
						break;
					}
					case RENDERER_API_VULKAN:
					{
						throw UnimplementedFeatureException("Vulkan API is not implemented yet");
						break;
					}
					case RENDERER_API_DIRECTX:
					{
						throw UnimplementedFeatureException("DirectX API is not implemented yet");
						break;
					}
					default:
					{
						break;
					}
				};

				break;
			}
			case API_WIN32:
			{
				throw UnimplementedFeatureException("Win32 API is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	bool Core::Init()
	{
		InitBaseAPI();
		InitContext();

		s_CoreInitialized = true;
		return s_CoreInitialized;
	}

	void Core::Quit()
	{
		if( !s_CoreInitialized )
			throw UninitializedObjectException("Core is not initialized");

		if( HasActiveWindow() )
		{
			for( auto& [_, window] : s_WindowPool )
			{
				if( window->Properties().IsActive )
					DestroyWindow(window);
			}
		}

		s_BaseAPI->Quit();
		s_BaseAPI = nullptr;
		s_Context = nullptr;
	}

	bool Core::HasActiveWindow()
	{
		for( auto& [_, window] : s_WindowPool )
		{
			if( window->Properties().IsActive )
				return true;
		}

		return false;
	}

	IWindow* Core::CreateWindow(const std::string& title)
	{
		if( !s_CoreInitialized )
			throw UninitializedObjectException("Core is not initialized");

		IWindow* window = nullptr;

		switch( GetPlatformBaseAPI() )
		{
			case API_GLFW:
			{
				window = new GLFW3_Window(title, s_Context);
				break;
			}
			case API_SDL:
			{
				window = new SDL3_Window(title, s_Context);
				break;
			}
			case API_WIN32:
			{
				throw UnimplementedFeatureException("Win32 API is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};

		if( !window )
			throw UninitializedObjectException("Failed to create window");

		window->Properties().Handle = GetUniqueHandle();
		s_WindowPool [window->GetWindowHandle()] = window;
		return window;
	}

	void Core::DestroyWindow(IWindow* window)
	{
		if( !s_CoreInitialized )
			throw UninitializedObjectException("Core is not initialized");

		if( !window )
			throw UninitializedObjectException("Window is not initialized");

		WindowHandle handle = window->Properties().Handle;
		s_WindowPool.erase(handle);

		delete window;
		window = nullptr;
	}

	std::shared_ptr<IContext> Core::GetContext()
	{
		if( !s_CoreInitialized )
			throw UninitializedObjectException("Core is not initialized");

		return s_Context;
	}

	void Core::SwapBuffers()
	{
		if( !s_CoreInitialized )
			throw UninitializedObjectException("Core is not initialized");

		if( !s_Context )
			throw UninitializedObjectException("Context is not initialized");

		for( auto& [_, window] : s_WindowPool )
		{
			if( !window->Properties().IsFocused )
				s_Context->SwapBuffers(window->Window());
		}
	}

	void Core::SetEventsCallbackFunc(const std::function<void(WindowHandle, Events&)>& callback)
	{
		for( auto& [_, window] : s_WindowPool )
			window->SetEventsCallbackFunc(callback);
	}

	void Core::PollEvents()
	{
		if( !s_CoreInitialized )
			throw UninitializedObjectException("Core is not initialized");

		for( auto& [_, window] : s_WindowPool )
		{
			if( !window->Properties().IsFocused )
				window->PollEvents();
		}
	}
}