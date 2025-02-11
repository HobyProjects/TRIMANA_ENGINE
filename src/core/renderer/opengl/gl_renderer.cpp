#include "core_pch.hpp"

namespace TE::Core
{
	void OpenGL_Renderer::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		#ifdef TE_DEBUG

			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(GLAD_DebugMessageCallBack, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

		#endif
	}

	void OpenGL_Renderer::Quit()
	{
	}

	void OpenGL_Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGL_Renderer::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGL_Renderer::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGL_Renderer::Draw(uint32_t indicesCount)
	{
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
	}
}