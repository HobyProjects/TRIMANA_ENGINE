#include "sdl_gl_context.hpp"
#include "exceptions.hpp"

namespace trimana::core {

	bool sdl_gl_context::make_context(){
		if (!m_native_window)
			throw null_pointer_exception("window is null");

		GLenum status = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
		if (status == GL_FALSE) {
			throw uninitialized_object_exception("Failed to initialize GLAD");
			return false;
		}

		SDL_GL_MakeCurrent((SDL_Window*)m_native_window, SDL_GL_CreateContext((SDL_Window*)m_native_window));
		SDL_GL_SetSwapInterval(1);
		return false;
	}

	void sdl_gl_context::swap_buffers(){
		if (!m_native_window)
			throw null_pointer_exception("window is null");
		SDL_GL_SwapWindow((SDL_Window*)m_native_window);
	}

	void sdl_gl_context::change_swap_interval(uint32_t interval){
		if (!m_native_window)
			throw null_pointer_exception("window is null");
		SDL_GL_SetSwapInterval(interval);
	}
}