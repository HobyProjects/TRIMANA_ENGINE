#pragma once

#include <memory>
#include <string>
#include <functional>

#include "base.hpp"
#include "events.hpp"
#include "renderer.hpp"

namespace TE::Core
{
	using WindowHandle  = uint32_t;
	using Native		= void*;

	enum WINDOW_STATE : uint32_t
	{
		WINDOW_FULLSCREEN 	= TE_BIT(0),
		WINDOW_MINIMIZED 	= TE_BIT(1),
		WINDOW_MAXIMIZED 	= TE_BIT(2),
		WINDOW_NORMAL 		= TE_BIT(3)
	};

	struct WindowColorBit
	{
		uint32_t RedBit{ 0 }, GreenBit{ 0 }, BlueBit{ 0 }, AlphaBit{ 0 };
		uint32_t DepthBit{ 0 }, DepthStencilBit{ 0 };
	};

	struct WindowProperties
	{
		std::string Title{ "" };                                     
		uint32_t Width{ 0 };                                         
		uint32_t height{ 0 };                                        
		WindowColorBit ColorBits;
		uint32_t RefreshRate{ 60 };                                  
		uint32_t FixedWidth{ 0 };                                    
		uint32_t FixedHeight{ 0 };                                  
		uint32_t MinWidth{ 1280 };                                   
		uint32_t MinHeight{ 720 };                                   
		uint32_t PosX{ 0 };                                         
		uint32_t PosY{ 0 }; 
		WindowHandle Handle{ 0 };
		int32_t PixelWidth{ 0 };                              
		int32_t PixelHeight{ 0 };                             
		WINDOW_STATE WindowState{ WINDOW_MAXIMIZED };        
		bool IsVSyncEnabled{ false };                               
		bool IsActive{ false };                                      
		bool IsFocused{ false };                                    
	};

	enum BASE_APIS : uint32_t
	{
		API_GLFW 	= TE_BIT(1),  
		API_SDL 	= TE_BIT(2), 
		API_WIN32 	= TE_BIT(3)  
	};

	class BaseAPI
	{
		public:
			BaseAPI() = default;
			virtual ~BaseAPI() = default;

			virtual bool Init() = 0;
			virtual void Quit() = 0;
			virtual BASE_APIS API() = 0;
	};

	enum CONTEXT_VERSION : uint32_t
	{
		RENDERER_GL_MAJOR_VERSION = 4,
		RENDERER_GL_MINOR_VERSION = 6
	};

	class IContext
	{
		public:
			IContext() = default;
			virtual ~IContext() = default;

			virtual void Attach(Native) = 0;
			virtual void Detach() = 0;

			virtual Native GetContext() const = 0;
			virtual void SwapBuffers(Native) = 0;
			virtual void SetInterval(uint32_t) = 0;
	};

	class IWindow
	{
		public:
			IWindow() = default;
			virtual ~IWindow() = default;

			virtual bool IsActive() const = 0;
			virtual Native Window() const = 0;
			virtual WindowProperties& Properties() = 0;
			virtual WindowHandle GetWindowHandle() = 0;
			virtual void PollEvents() = 0;
			virtual void SwapBuffers() = 0;
			virtual void SetEventsCallbackFunc(const std::function<void(WindowHandle, Events&)>&) = 0;
	};
}