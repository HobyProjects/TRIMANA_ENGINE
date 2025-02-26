#include "core_pch.hpp"

namespace TE::Core
{
	static bool s_Initialized{ false };
	static std::function<void(WindowHandle, Events&)> s_CallbackFunc{ nullptr };

	bool GLFW3_API::Init()
	{
		if( !glfwInit() )
		{
			const char* lastError{ nullptr };
			int32_t errorCode = glfwGetError(&lastError);
			TE_ASSERT(false, "Failed to initialize GLFW | GLFW Error Code: {0} | GLFW Error: {1}", errorCode, lastError);
			return ( s_Initialized = false );
		}

		TE_CORE_INFO("GLFW initialized successfully");
		return ( s_Initialized = true );
	}

	void GLFW3_API::Quit()
	{
		if( s_Initialized )
		{
			glfwTerminate();
			s_Initialized = false;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	static GLFWwindow* s_Window{ nullptr };
	static WindowProperties s_Properties{};
	static std::weak_ptr<IContext> s_Context;

	GLFW3_Window::GLFW3_Window(const std::string& title, const std::shared_ptr<IContext> context)
	{
		s_Context = context;
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		if( mode != nullptr )
		{
			s_Properties.Width = mode->width;
			s_Properties.Height = mode->Height;
			s_Properties.FixedWidth = mode->width;
			s_Properties.FixedHeight = mode->Height;
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
			s_Properties.Height = 720;
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
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, RENDERER_GL_MAJOR_VERSION);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, RENDERER_GL_MINOR_VERSION);
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

		s_Window = glfwCreateWindow(s_Properties.Width, s_Properties.Height, s_Properties.Title.c_str(), nullptr, nullptr);
		if( s_Window != nullptr )
		{
			TE_CORE_INFO("GLFW window created successfully");
			glfwSetWindowSizeLimits(s_Window, s_Properties.MinWidth, s_Properties.MinHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
			glfwGetFramebufferSize(s_Window, &s_Properties.PixelWidth, &s_Properties.PixelHeight);

			if( !s_Context.expired() )
			{
				auto context = s_Context.lock();
				context->Attach(s_Window);
			}

			s_Properties.IsActive = true;
			s_Properties.IsFocused = glfwGetWindowAttrib(s_Window, GLFW_FOCUSED);
			s_Properties.IsVSyncEnabled = true;
		}
		else
		{
			const char* lastError{ nullptr };
			int32_t errorCode = glfwGetError(&lastError);
			TE_ASSERT(s_Window, "Failed to create GLFW Window | GLFW Error Code:{0} | Error: {1}", errorCode, lastError);
			return;
		}
	}

	GLFW3_Window::~GLFW3_Window()
	{
		if( s_Window != nullptr )
		{
			glfwDestroyWindow(s_Window);
			s_Window = nullptr;
		}
	}

	bool GLFW3_Window::IsActive() const
	{
		return s_Properties.IsActive;
	}

	Native GLFW3_Window::Window() const
	{
		return s_Window;
	}

	WindowProperties& GLFW3_Window::Properties()
	{
		return s_Properties;
	}

	WindowHandle GLFW3_Window::GetWindowHandle()
	{
		return s_Properties.Handle;
	}

	static void glfwSetEventsCallbacks()
	{
		glfwSetWindowCloseCallback(s_Window, [](GLFWwindow* window)
		{
			EventWindowClose windowCloseEvent;
			s_CallbackFunc(s_Properties.Handle, windowCloseEvent);
		});

		glfwSetWindowSizeCallback(s_Window, [](GLFWwindow* window, int width, int Height)
		{
			EventWindowResize windowResizeEvent(width, Height);
			s_Properties.Width = width;
			s_Properties.Height = Height;
			s_CallbackFunc(s_Properties.Handle, windowResizeEvent);
		});

		glfwSetWindowFocusCallback(s_Window, [](GLFWwindow* window, int focused)
		{
			if( focused )
			{
				EventWindowFocusGain windowFocusEvent;
				s_Properties.IsFocused = true;
				s_CallbackFunc(s_Properties.Handle, windowFocusEvent);
			}
			else
			{
				EventWindowFocusLost windowLostFocusEvent;
				s_Properties.IsFocused = false;
				s_CallbackFunc(s_Properties.Handle, windowLostFocusEvent);
			}
		});

		glfwSetWindowIconifyCallback(s_Window, [](GLFWwindow* window, int iconified)
		{
			if( iconified )
			{
				EventWindowMinimize windowMinimizeEvent;
				s_Properties.WindowState = WINDOW_MINIMIZED;
				s_CallbackFunc(s_Properties.Handle, windowMinimizeEvent);
			}
		});

		glfwSetWindowMaximizeCallback(s_Window, [](GLFWwindow* window, int maximized)
		{
			if( maximized )
			{
				EventWindowMaximaize windowMaximizeEvent;
				s_Properties.WindowState = WINDOW_MAXIMIZED;
				s_CallbackFunc(s_Properties.Handle, windowMaximizeEvent);
			}

		});

		glfwSetWindowPosCallback(s_Window, [](GLFWwindow* window, int x, int y)
		{
			EventWindowPosChange windowMoveEvent(x, y);
			s_Properties.PosX = x;
			s_Properties.PosY = y;
			s_CallbackFunc(s_Properties.Handle, windowMoveEvent);
		});

		glfwSetFramebufferSizeCallback(s_Window, [](GLFWwindow* window, int width, int Height)
		{
			EventWindowPixelSizeChange windowPixelSizeEvent(width, Height);
			s_Properties.PixelWidth = width;
			s_Properties.PixelHeight = Height;
			s_CallbackFunc(s_Properties.Handle, windowPixelSizeEvent);
		});

		glfwSetKeyCallback(s_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch( action )
			{
				case GLFW_PRESS:
				{
					EventKeyboardKeyPress keyPressEvent(static_cast<KEY>(key));
					s_CallbackFunc(s_Properties.Handle, keyPressEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					EventKeyboardKeyRelease keyReleaseEvent(static_cast<KEY>(key));
					s_CallbackFunc(s_Properties.Handle, keyReleaseEvent);
					break;
				}
				case GLFW_REPEAT:
				{
					EventKeyboardKeyRepeate keyPressEvent(static_cast<KEY>(key));
					s_CallbackFunc(s_Properties.Handle, keyPressEvent);
					break;
				}
			}

		});

		glfwSetCharCallback(s_Window, [](GLFWwindow* window, unsigned int codepoint)
		{
			EventKeyboardKeyChar charInputEvent(codepoint);
			s_CallbackFunc(s_Properties.Handle, charInputEvent);
		});

		glfwSetMouseButtonCallback(s_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			switch( action )
			{
				case GLFW_PRESS:
				{
					EventMouseButtonDown buttonPressEvent(static_cast<MOUSE_BUTTON>( button ));
					s_CallbackFunc(s_Properties.Handle, buttonPressEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					EventMouseButtonUp buttonReleaseEvent(static_cast<MOUSE_BUTTON>( button ));
					s_CallbackFunc(s_Properties.Handle, buttonReleaseEvent);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(s_Window, [](GLFWwindow* window, double x, double y)
		{
			EventMouseCursorMove mouseMoveEvent(x, y);
			s_CallbackFunc(s_Properties.Handle, mouseMoveEvent);
		});

		glfwSetScrollCallback(s_Window, [](GLFWwindow* window, double x, double y)
		{
			EventMouseWheelScroll mouseScrollEvent(x, y);
			s_CallbackFunc(s_Properties.Handle, mouseScrollEvent);
		});

		glfwSetCursorEnterCallback(s_Window, [](GLFWwindow* window, int entered)
		{
			if( entered )
			{
				EventMouseCursorWindowEnter mouseEnterEvent;
				s_CallbackFunc(s_Properties.Handle, mouseEnterEvent);
			}
			else
			{
				EventMouseCursorWindowLeave mouseLeaveEvent;
				s_CallbackFunc(s_Properties.Handle, mouseLeaveEvent);
			}
		});
	}


	void GLFW3_Window::SetEventsCallbackFunc(const std::function<void(WindowHandle, Events&)>& callbackFunc)
	{
		s_CallbackFunc = callbackFunc;
		glfwSetEventsCallbacks();
	}

	void GLFW3_Window::PollEvents()
	{
		glfwWaitEvents();
	}

	void GLFW3_Window::SwapBuffers()
	{
		if( !s_Context.expired() )
		{
			auto context = s_Context.lock();
			context->SwapBuffers(s_Window);
		}
	}
}