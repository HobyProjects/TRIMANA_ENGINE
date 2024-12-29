#include "sdl_gl_context.hpp"
#include "exceptions.hpp"

namespace TE::Core
{
	static Native s_Window{ nullptr };
	std::once_flag SDL_GL_Context::s_InitRendererAPI;

	void SDL_GL_Context::InitRendereringAPI()
	{
		if( !gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress) )
		{
			throw UninitializedObjectException("Failed to initialize GLAD");
		}
	}

	bool SDL_GL_Context::MakeContext(Native window)
	{
		if( !window )
			throw NullPointerException("window is null");

		s_Window = window;
		SDL_GL_MakeCurrent((SDL_Window*) s_Window, SDL_GL_CreateContext((SDL_Window*) s_Window));
		SDL_GL_SetSwapInterval(1);



		TE_CORE_INFO("GLAD successfully initialized");
		return false;
	}

	Native SDL_GL_Context::GetContext() const
	{
		return SDL_GL_GetCurrentContext();
	}

	void SDL_GL_Context::SwapBuffers()
	{
		SDL_GL_SwapWindow((SDL_Window*) s_Window);
	}

	void SDL_GL_Context::SetInterval(uint32_t interval)
	{
		SDL_GL_SetSwapInterval(interval);
	}
}