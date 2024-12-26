#pragma once

#include <memory>
#include <string>

#include "base.hpp"
#include "renderer.hpp"

namespace trimana::core
{
	enum class window_state
	{
		fullscreen = 0,
		minimized = 1,
		maximized = 2,
		normal = 3
	};

	struct window_properties
	{
		std::string title{ "" };                                      /**< The title of the window. */
		uint32_t width{ 0 };                                          /**< Width of the window. */
		uint32_t height{ 0 };                                         /**< Height of the window. */
		uint32_t red_color_bits{ 8 };                                 /**< The number of red color bits. */
		uint32_t green_color_bits{ 8 };                               /**< The number of green color bits. */
		uint32_t blue_color_bits{ 8 };                                /**< The number of blue color bits. */
		uint32_t alpha_color_bits{ 8 };                               /**< The number of alpha color bits. */
		uint32_t depth_color_bits{ 24 };                              /**< The number of depth color bits. */
		uint32_t stencil_color_bits{ 8 };                             /**< The number of stencil color bits. */
		uint32_t refresh_rate{ 60 };                                  /**< The refresh rate of the window. */
		uint32_t fixed_width{ 0 };                                    /**< If the window has a fixed width, this is the value. */
		uint32_t fixed_height{ 0 };                                   /**< If the window has a fixed height, this is the value. */
		uint32_t min_width{ 1280 };                                   /**< The minimum width of the window. */
		uint32_t min_height{ 720 };                                   /**< The minimum height of the window. */
		uint32_t pos_x{ 0 };                                          /**< The x position of the window. */
		uint32_t pos_y{ 0 };                                          /**< The y position of the window. */
		int32_t framebuffer_width{ 0 };                               /**< The width of the framebuffer. */
		int32_t framebuffer_height{ 0 };                              /**< The height of the framebuffer. */
		window_state window_state{ window_state::maximized };         /**< The state of the window. */
		bool is_vsync_enabled{ false };                               /**< If vsync is enabled or not. */
		bool is_focused{ false };                                     /**< If the window is focused or not. */
		bool is_active{ false };                                      /**< If the window is active or not. */
	};

	enum class platform_service_apis
	{
		glfw_api = TRIMANA_BIT(1),  /**< GLFW API bit flag. */
		sdl_api = TRIMANA_BIT(2),  /**< SDL API bit flag. */
		win32_api = TRIMANA_BIT(3)   /**< Win32 API bit flag. */
	};

	class platform_service_api
	{
	public:
		platform_service_api() = default;
		virtual ~platform_service_api() = default;

		virtual bool init() = 0;
		virtual void quit() = 0;
		virtual platform_service_apis api() = 0;
	};

	enum class rendering_context_version
	{
		opengl_api_major_version = 4,
		opengl_api_minor_version = 6
	};

	class context
	{
	public:
		context() = default;
		virtual ~context() = default;

		virtual bool make_context() = 0;
		virtual void swap_buffers() = 0;
		virtual void change_swap_interval(uint32_t interval) = 0;

	public:
		class context_builder
		{
		private:
			context_builder() = default;
			~context_builder() = default;

		public:
			static std::shared_ptr<context> create(void* native_window, rendering_api api);
		};
	};

	class window
	{
	public:
		window() = default;
		virtual ~window() = default;

		virtual void* native_window() const = 0;
		virtual window_properties* properties() = 0;
		virtual void swap_buffers() const = 0;
		virtual std::shared_ptr<context> window_context() const = 0;

	public:
		class window_builder
		{
		private:
			window_builder() = default;
			~window_builder() = default;

		public:
			static std::shared_ptr<window> create(const std::string& title);
			static const std::shared_ptr<platform_service_api>& get_platform_service_api();
		};
	};
}