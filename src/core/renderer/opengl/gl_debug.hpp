#pragma once

#include <glad/glad.h>

namespace TE::Core
{
	#ifdef TE_DEBUG

		void GLAPIENTRY GLAD_DebugMessageCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	
	#endif
}