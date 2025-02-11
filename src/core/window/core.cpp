#include "core_pch.hpp"

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

	static void InitializeBaseAPI()
	{
		switch( GetPlatformBaseAPI() )
		{
			case API_GLFW:
			{
				s_BaseAPI = std::make_shared<GLFW3_API>();
				if( !s_BaseAPI->Init() )
					TE_ASSERT(false, "Failed to initialize the base API -> GLFW");

				break;
			}
			case API_SDL:
			{
				s_BaseAPI = std::make_shared<SDL3_API>();
				if( !s_BaseAPI->Init() )
					TE_ASSERT(false, "Failed to initialize the base API -> SDL")

				break;
			}
			case API_WIN32:
			{
				TE_ASSERT(false, "Win32 is not implemented yet!");
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

	static std::shared_ptr<IContext> s_Context{};
	static std::unordered_map<WindowHandle, IWindow*> s_WindowPool{};

	static WindowHandle GetUniqueHandle()
	{
		static WindowHandle s_Handle = 0;
		return s_Handle++;
	}

	static void CreateContextObject()
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
						TE_ASSERT(false, "Vulkan API is not implemented yet!");
						break;
					}
					case RENDERER_API_DIRECTX:
					{
						TE_ASSERT(false, "DirectX API is not implemented yet!");
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
						TE_ASSERT(false, "Vulkan API is not implemented yet!");
						break;
					}
					case RENDERER_API_DIRECTX:
					{
						TE_ASSERT(false, "DirectX API is not implemented yet!");
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
				TE_ASSERT(false, "Win32 is not implemented yet!");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	void Core::Init()
	{
		InitializeBaseAPI();
		CreateContextObject();

		Renderer::Init();
		BatchRenderer2D::Init();

		s_CoreInitialized = true;
	}

	void Core::Quit()
	{
		TE_ASSERT(s_CoreInitialized, "Initialize the core before calling this method. Use TE::Core::Core::Init() method to initalize the core");

		for( auto& [handle, window] : s_WindowPool )
		{
			if( window != nullptr || window->Properties().IsActive )
				TE_CORE_WARN("Window with handle {0} is still active, destroying window...", handle);

			delete window;
			window = nullptr;
		}

		BatchRenderer2D::Quit();
		Renderer::Quit();

		s_BaseAPI->Quit();
		s_BaseAPI = nullptr;
	}

	Window Core::CreateWindow(const std::string& title)
	{
		TE_ASSERT(s_CoreInitialized, "Initialize the core before calling this method. Use TE::Core::Core::Init() method to initalize the core");

		Window window = nullptr;

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
				TE_ASSERT(false, "Win32 API is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};

		TE_ASSERT(window, "Unable to create the window");

		window->Properties().Handle = GetUniqueHandle();
		s_WindowPool [window->GetWindowHandle()] = window;
		return window;
	}

	void Core::DestroyWindow(Window window)
	{
		TE_ASSERT(s_CoreInitialized, "Initialize the core before calling this method. Use TE::Core::Core::Init() method to initalize the core");
		TE_ASSERT(window, "This window is not valid, Unable to destroy it.");

		WindowHandle handle = window->Properties().Handle;
		s_WindowPool.erase(handle);

		delete window;
		window = nullptr;
	}

	std::shared_ptr<Context> Core::GetContext()
	{
		TE_ASSERT(s_CoreInitialized, "Initialize the core before calling this method. Use TE::Core::Core::Init() method to initalize the core");
		return s_Context;
	}

}