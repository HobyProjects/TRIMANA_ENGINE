#include "sdl_gl_context.hpp"
#include "exceptions.hpp"

namespace TE::Core
{
	SDL_GL_Context::SDL_GL_Context()
	{

	}

	void SDL_GL_Context::Attach(Native window)
	{
		if( !window )
			throw NullPointerException("window is null");

		SDL_GL_MakeCurrent((SDL_Window*) window, SDL_GL_CreateContext((SDL_Window*) window));
		static bool glad_initialized = false;
		if( !glad_initialized )
		{
			if( !gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress) )
			{
				throw UninitializedObjectException("Failed to initialize GLAD");
			}

			glad_initialized = true;
			TE_CORE_INFO("GLAD successfully initialized");
		}
	}

	void SDL_GL_Context::Detach()
	{
		SDL_GL_MakeCurrent(nullptr, nullptr);
	}

	Native SDL_GL_Context::GetContext() const
	{
		return SDL_GL_GetCurrentContext();
	}

	void SDL_GL_Context::SwapBuffers(Native window)
	{
		if( !window )
			throw NullPointerException("window is null");

		SDL_GL_SwapWindow((SDL_Window*) window);
	}

	void SDL_GL_Context::SetInterval(uint32_t interval)
	{
		SDL_GL_SetSwapInterval(interval);
	}
}