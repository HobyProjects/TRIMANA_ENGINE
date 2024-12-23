#include "gl_renderer.hpp"
#include "gl_debug.hpp"

#include <glad/glad.h>

namespace trimana::core {

	void gl_renderer::init() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

#ifdef TRIMANA_DEBUG

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debug_message_callback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

#endif
	}

	void gl_renderer::quit() {
	}

	void gl_renderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void gl_renderer::clear_color(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void gl_renderer::set_viewport(int32_t x, int32_t y, int32_t width, int32_t height) {
		glViewport(x, y, width, height);
	}
}