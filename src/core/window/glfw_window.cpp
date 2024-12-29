#include "glfw_window.hpp"
#include "exceptions.hpp"
#include "renderer.hpp"
#include "log.hpp"

namespace TE::Core
{
	static bool s_Initialized{ false };

	bool GLFW_API::Init()
	{
		if( !glfwInit() )
		{
			throw UninitializedObjectException("Failed to initialize GLFW");
			return ( s_Initialized = false );
		}

		TE_CORE_INFO("GLFW initialized successfully");
		return ( s_Initialized = true );
	}

	void GLFW_API::Quit()
	{
		if( s_Initialized )
		{
			glfwTerminate();
			s_Initialized = false;
		}
	}

	static GLFWwindow* s_Window{ nullptr };
	static WindowProperties s_Properties{};

	GLFW_Window::GLFW_Window(const std::string& title)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		if( mode != nullptr )
		{
			s_Properties.Width = mode->width;
			s_Properties.height = mode->height;
			s_Properties.FixedWidth = mode->width;
			s_Properties.FixedHeight = mode->height;
			s_Properties.MinWidth = 1024;
			s_Properties.MinHeight = 720;
			s_Properties.ColorBits.RedBit = mode->redBits;
			s_Properties.ColorBits.GreenBit = mode->greenBits;
			s_Properties.ColorBits.BlueBit = mode->blueBits;
			s_Properties.ColorBits.AlphaBit = 8;
			s_Properties.ColorBits.DepthStencilBit = 8;
			s_Properties.ColorBits.DepthBit = 24;
			s_Properties.RefreshRate = mode->refreshRate;

		}
		else
		{
			TE_CORE_WARN("Failed to get video mode, using default values");
			s_Properties.Width = 1280;
			s_Properties.height = 720;
			s_Properties.FixedWidth = 0;
			s_Properties.FixedHeight = 0;
			s_Properties.MinWidth = 1024;
			s_Properties.MinHeight = 720;
			s_Properties.ColorBits.RedBit = 8;
			s_Properties.ColorBits.GreenBit = 8;
			s_Properties.ColorBits.BlueBit = 8;
			s_Properties.ColorBits.AlphaBit = 8;
			s_Properties.ColorBits.DepthStencilBit = 8;
			s_Properties.ColorBits.DepthBit = 24;
			s_Properties.RefreshRate = 60;
		}

		s_Properties.Title = title;

		if( Renderer::API() & RENDERER_API_OPENGL)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR_VERSION);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR_VERSION);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
			glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

			#if defined(TE_DEBUG)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			#endif
		}

		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_RED_BITS, s_Properties.ColorBits.RedBit);
		glfwWindowHint(GLFW_GREEN_BITS, s_Properties.ColorBits.GreenBit);
		glfwWindowHint(GLFW_BLUE_BITS, s_Properties.ColorBits.BlueBit);
		glfwWindowHint(GLFW_ALPHA_BITS, s_Properties.ColorBits.AlphaBit);
		glfwWindowHint(GLFW_REFRESH_RATE, s_Properties.RefreshRate);
		glfwWindowHint(GLFW_DEPTH_BITS, s_Properties.ColorBits.DepthBit);
		glfwWindowHint(GLFW_STENCIL_BITS, s_Properties.ColorBits.DepthStencilBit);

		s_Window = glfwCreateWindow(s_Properties.Width, s_Properties.height, s_Properties.Title.c_str(), nullptr, nullptr);
		if( s_Window != nullptr )
		{
			TE_CORE_INFO("GLFW window created successfully");
			glfwSetWindowSizeLimits(s_Window, s_Properties.MinWidth, s_Properties.MinHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
			glfwGetFramebufferSize(s_Window, &s_Properties.PixelWidth, &s_Properties.PixelHeight);

			s_Properties.IsActive = true;
			s_Properties.IsFocused = glfwGetWindowAttrib(s_Window, GLFW_FOCUSED);
			s_Properties.IsVSyncEnabled = true;
		}
		else
		{
			throw BaseAPIException("Failed to create GLFW window");
			return;
		}
	}

	GLFW_Window::~GLFW_Window()
	{
		if( s_Window != nullptr )
		{
			glfwDestroyWindow(s_Window);
			s_Window = nullptr;
		}
	}

	Native GLFW_Window::Window() const
	{
		return s_Window;
	}

	WindowProperties& GLFW_Window::Properties()
	{
		return s_Properties;
	}
}