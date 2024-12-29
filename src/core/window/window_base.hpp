#pragma once

#include <memory>
#include <string>
#include <functional>

#include "base.hpp"
#include "events.hpp"
#include "renderer.hpp"

namespace trimana::core
{
	using window_handle = uint32_t;

	enum class window_state
	{
		fullscreen 	= 0,
		minimized 	= 1,
		maximized 	= 2,
		normal 		= 3
	};

	struct window_properties
	{
		std::string title{ "" };                                     
		uint32_t width{ 0 };                                         
		uint32_t height{ 0 };                                        
		uint32_t red_color_bits{ 8 };                                 
		uint32_t green_color_bits{ 8 };                               
		uint32_t blue_color_bits{ 8 };                                
		uint32_t alpha_color_bits{ 8 };                              
		uint32_t depth_color_bits{ 24 };                              
		uint32_t stencil_color_bits{ 8 };                             
		uint32_t refresh_rate{ 60 };                                  
		uint32_t fixed_width{ 0 };                                    
		uint32_t fixed_height{ 0 };                                  
		uint32_t min_width{ 1280 };                                   
		uint32_t min_height{ 720 };                                   
		uint32_t pos_x{ 0 };                                         
		uint32_t pos_y{ 0 }; 
		window_handle handle{ 0 };
		int32_t framebuffer_width{ 0 };                              
		int32_t framebuffer_height{ 0 };                             
		window_state window_state{ window_state::maximized };        
		bool is_vsync_enabled{ false };                               
		bool is_active{ false };                                      
		bool is_focused{ false };                                    
	};

	enum class base_apis
	{
		glfw_api 	= TRIMANA_BIT(1),  
		sdl_api 	= TRIMANA_BIT(2), 
		win32_api 	= TRIMANA_BIT(3)  
	};

	class base_api
	{
		public:
			base_api() = default;
			virtual ~base_api() = default;

			virtual bool init() = 0;
			virtual void quit() = 0;
			virtual base_apis api() = 0;
	};

	enum class context_version
	{
		opengl_major_version = 4,
		opengl_minor_version = 6
	};

	class context_base
	{
		public:
			context_base() = default;
			virtual ~context_base() = default;

			virtual bool make_context() = 0;
			virtual void swap_buffers() = 0;
			virtual void change_swap_interval(uint32_t interval) = 0;
	};

	class window_base
	{
		public:
			window_base() = default;
			virtual ~window_base() = default;

			virtual void* native_window() const = 0;
			virtual window_properties* properties() = 0;
			virtual void swap_buffers() const = 0;
			virtual std::shared_ptr<context_base> context() const = 0;
			virtual std::shared_ptr<base_api> base() const = 0;
			virtual void set_callback(const std::function<void(events&)>&) const = 0;
			
	};
}