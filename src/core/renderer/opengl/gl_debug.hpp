#pragma once
#include <glad/glad.h>

namespace trimana::core {
#ifdef TRIMANA_DEBUG
	void GLAPIENTRY debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
#endif
}