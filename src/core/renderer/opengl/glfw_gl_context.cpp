#include "glfw_gl_context.hpp"
#include "exceptions.hpp"

namespace TE::Core
{
	static Native s_Window{ nullptr };
	std::once_flag GLFW_GL_Context::s_InitRendererAPI;

	void GLFW_GL_Context::InitRendereringAPI()
	{
		if( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) )
		{
			throw UninitializedObjectException("Failed to initialize GLAD");
		}

	}

	bool GLFW_GL_Context::MakeContext(Native window)
	{
		if( !window )
			throw NullPointerException("window is null");

		s_Window = window;
		glfwMakeContextCurrent((GLFWwindow*) s_Window);
		glfwSwapInterval(1);

		std::call_once(s_InitRendererAPI, InitRendereringAPI);

		TE_CORE_INFO("GLAD successfully initialized");
		return true;
	}

	Native GLFW_GL_Context::GetContext() const
	{
		return glfwGetCurrentContext();
	}

	void GLFW_GL_Context::SwapBuffers()
	{
		glfwSwapBuffers((GLFWwindow*) s_Window);
	}

	void GLFW_GL_Context::SetInterval(uint32_t interval)
	{
		glfwSwapInterval(interval);
	}
}