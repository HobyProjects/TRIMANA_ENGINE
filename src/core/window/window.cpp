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
	/**********************************************
	*		  INITIALIZING BASE API			      *
	***********************************************/
	static std::once_flag s_InitBaseAPI;
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
				s_BaseAPI = std::make_shared<GLFW_API>();
				if( !s_BaseAPI->Init() )
					throw UninitializedObjectException("Failed to initialize the base API : GLFW");

				break;
			}
			case API_SDL:
			{
				s_BaseAPI = std::make_shared<SDL_API>();
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
}