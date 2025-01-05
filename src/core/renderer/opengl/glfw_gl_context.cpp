#include "core_pch.hpp"

namespace TE::Core
{
	GLFW_GL_Context::GLFW_GL_Context()
	{

	}

	void GLFW_GL_Context::Attach(Native window)
	{
		TE_ASSERT(window, "The Native window is null");
		glfwMakeContextCurrent((GLFWwindow*) window);
		glfwSwapInterval(1);

		static bool glad_initialized = false;
		if( !glad_initialized )
		{
			TE_ASSERT(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "Failed to load OpenGL!");
			glad_initialized = true;
			TE_CORE_INFO("GLAD successfully initialized");
		}
	}

	void GLFW_GL_Context::Detach()
	{
		glfwMakeContextCurrent(nullptr);
	}

	Native GLFW_GL_Context::GetContext() const
	{
		return glfwGetCurrentContext();
	}

	void GLFW_GL_Context::SwapBuffers(Native window)
	{
		if( !window )
			throw NullPointerException("window is null");

		glfwSwapBuffers((GLFWwindow*) window);
	}

	void GLFW_GL_Context::SetInterval(uint32_t interval)
	{
		glfwSwapInterval(interval);
	}
}