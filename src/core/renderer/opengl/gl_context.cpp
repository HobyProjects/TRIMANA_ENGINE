#include "gl_context.hpp"
#include "exceptions.hpp"

namespace trimana::core {

	bool gl_context::make_context() {
		if (!m_native_window)
			throw null_pointer_exception("window is null");

		GLenum status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == GL_FALSE) {
			throw uninitialize_exception("Failed to initialize GLAD");
			return false;
		}

		glfwMakeContextCurrent((GLFWwindow*)m_native_window);
		glfwSwapInterval(1);
		return true;
	}

	void gl_context::swap_buffers() {
		if (!m_native_window)
			throw null_pointer_exception("window is null");
		glfwSwapBuffers((GLFWwindow*)m_native_window);
	}

	void gl_context::change_swap_interval(uint32_t interval) {
		if (!m_native_window)
			throw null_pointer_exception("window is null");
		glfwSwapInterval(interval);
	}
}